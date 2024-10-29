#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct ItemBox {
    char type;    // 'W', 'A', 'O'
    string name;  // accessory code or number for W/A
};

struct Monster {
    string name;
    int w, a, h, e;
    int max_h;
    bool is_boss;
    int x, y;
    bool alive;
};

int N, M;
vector<string> grid;
string commands;

pair<int, int> player_pos;
pair<int, int> start_pos;

struct Player {
    int lv = 1;
    int max_hp = 20;
    int hp = 20;
    int base_att = 2;
    int base_def = 2;
    int exp = 0;

    int weapon = 0;
    int armor = 0;

    set<string> accessories;

    bool alive = true;
    bool win = false;

    bool haveAccessory(string s) {
        return accessories.find(s) != accessories.end();
    }

    int getTotalAtt() {
        int att = base_att + weapon;
        return att;
    }

    int getTotalDef() {
        int def = base_def + armor;
        return def;
    }

    int getNextLevelExp() {
        return lv * 5;
    }

    void levelUp() {
        lv++;
        max_hp += 5;
        base_att += 2;
        base_def += 2;
        hp = max_hp;
        exp = 0;
    }
};

Player player;

map<pair<int, int>, ItemBox> item_boxes;
map<pair<int, int>, Monster> monsters;

int turn = 0;
string game_result = "";
string death_reason = "";

int dx[128], dy[128];

void init() {
    dx['L'] = 0;
    dy['L'] = -1;
    dx['R'] = 0;
    dy['R'] = 1;
    dx['U'] = -1;
    dy['U'] = 0;
    dx['D'] = 1;
    dy['D'] = 0;
}

void levelUpIfNeeded() {
    while (player.exp >= player.getNextLevelExp()) {
        player.exp -= player.getNextLevelExp();
        player.levelUp();
    }
}

void gameOver(string reason) {
    player.alive = false;
    death_reason = reason;
}

void gameWin() {
    player.win = true;
}

void processTrap(int x, int y) {
    int dmg = player.haveAccessory("DX") ? 1 : 5;
    player.hp -= dmg;
    if (player.hp <= 0) {
        if (player.haveAccessory("RE")) {
            // Reincarnation
            player.accessories.erase("RE");
            player.hp = player.max_hp;
            player_pos = start_pos;
            // Reset monsters
            for (auto& m : monsters) {
                m.second.h = m.second.max_h;
                m.second.alive = true;
            }
        } else {
            gameOver("SPIKE TRAP");
            return;
        }
    }
}

void processItem(int x, int y) {
    ItemBox box = item_boxes[{x, y}];
    if (box.type == 'W') {
        player.weapon = stoi(box.name);
    } else if (box.type == 'A') {
        player.armor = stoi(box.name);
    } else if (box.type == 'O') {
        if (player.accessories.size() < 4 && !player.haveAccessory(box.name)) {
            player.accessories.insert(box.name);
        }
    }
    item_boxes.erase({x, y});
    grid[x][y] = '.';
}

void processMonster(int x, int y) {
    Monster& mon = monsters[{x, y}];
    int mon_att = mon.w;
    int mon_def = mon.a;
    int& mon_hp = mon.h;  // current monster's HP

    if (mon.is_boss && player.haveAccessory("HU")) {
        player.hp = player.max_hp;
    }

    bool player_first_attack = true;
    bool monster_first_attack = true;
    while (true) {
        // Player's turn
        int player_att = player.getTotalAtt();
        if (player_first_attack) {
            if (player.haveAccessory("CO")) {
                if (player.haveAccessory("DX")) {
                    player_att *= 3;
                } else {
                    player_att *= 2;
                }
            }
        }
        int damage_to_mon = max(1, player_att - mon_def);
        mon_hp -= damage_to_mon;
        if (mon_hp <= 0) {
            // Monster dies
            mon.alive = false;
            grid[x][y] = '.';
            int exp_gain = mon.e;
            if (player.haveAccessory("EX")) {
                exp_gain = exp_gain * 12 / 10;  // 1.2x, drop decimal
            }
            player.exp += exp_gain;
            levelUpIfNeeded();
            if (player.haveAccessory("HR")) {
                player.hp += 3;
                if (player.hp > player.max_hp) {
                    player.hp = player.max_hp;
                }
            }
            if (mon.is_boss) {
                gameWin();
            }
            // Move player to monster's position
            player_pos = {x, y};
            break;
        }

        // Monster's turn
        int damage_to_player = max(1, mon_att - player.getTotalDef());
        if (mon.is_boss && monster_first_attack && player.haveAccessory("HU")) {
            damage_to_player = 0;
        }
        player.hp -= damage_to_player;
        if (player.hp <= 0) {
            if (player.haveAccessory("RE")) {
                // Reincarnation
                player.accessories.erase("RE");
                player.hp = player.max_hp;
                player_pos = start_pos;
                // Reset monsters
                mon.h = mon.max_h;
                // for (auto& m : monsters) {
                //     m.second.h = m.second.max_h;
                //     m.second.alive = true;
                // }
                // break;
                break;
            } else {
                gameOver(mon.name);
                return;
            }
        }

        // Prepare for next round
        player_first_attack = false;
        monster_first_attack = false;
    }
    if (!player.alive || player.win) {
        return;
    }
}

void processMove(char cmd) {
    if (!player.alive || player.win) return;
    turn++;
    int nx = player_pos.first + dx[cmd];
    int ny = player_pos.second + dy[cmd];
    if (nx < 0 || nx >= N || ny < 0 || ny >= M || grid[nx][ny] == '#') {
        // Invalid move, but if on trap, apply damage again
        if (grid[player_pos.first][player_pos.second] == '^') {
            processTrap(player_pos.first, player_pos.second);
        }
        return;
    }
    player_pos = {nx, ny};
    char tile = grid[nx][ny];
    if (tile == '^') {
        processTrap(nx, ny);
    } else if (tile == 'B') {
        processItem(nx, ny);
    } else if (tile == '&' || tile == 'M') {
        processMonster(nx, ny);
    }
    // No need to handle '.', already moved
}

void processGame() {
    for (char cmd : commands) {
        if (!player.alive || player.win) break;
        processMove(cmd);
    }
}

void outputResult() {
    for (int i = 0; i < N; i++) {
        string row = grid[i];
        for (int j = 0; j < M; j++) {
            if (player.alive && player_pos == make_pair(i, j)) {
                cout << '@';
            } else {
                cout << row[j];
            }
        }
        cout << '\n';
    }
    cout << "Passed Turns : " << turn << '\n';
    cout << "LV : " << player.lv << '\n';
    cout << "HP : " << max(0, player.hp) << '/' << player.max_hp << '\n';
    cout << "ATT : " << player.base_att << '+' << player.weapon << '\n';
    cout << "DEF : " << player.base_def << '+' << player.armor << '\n';
    cout << "EXP : " << player.exp << '/' << player.getNextLevelExp() << '\n';
    if (player.win) {
        cout << "YOU WIN!\n";
    } else if (!player.alive) {
        cout << "YOU HAVE BEEN KILLED BY " << death_reason << "..\n";
    } else {
        cout << "Press any key to continue.\n";
    }
}

int main() {
    init();
    cin >> N >> M;
    grid.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> grid[i];
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == '@') {
                player_pos = {i, j};
                start_pos = {i, j};
                grid[i][j] = '.';
            }
        }
    }
    cin >> commands;
    int K;
    K = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == '&' || grid[i][j] == 'M') {
                K++;
            }
        }
    }
    for (int i = 0; i < K; i++) {
        int r, c;
        string name;
        int w, a, h, e;
        cin >> r >> c >> name >> w >> a >> h >> e;
        r--;
        c--;
        Monster mon;
        mon.name = name;
        mon.w = w;
        mon.a = a;
        mon.h = h;
        mon.max_h = h;
        mon.e = e;
        mon.is_boss = (grid[r][c] == 'M');
        mon.x = r;
        mon.y = c;
        mon.alive = true;
        monsters[{r, c}] = mon;
    }
    int L;
    L = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 'B') {
                L++;
            }
        }
    }
    for (int i = 0; i < L; i++) {
        int r, c;
        char t;
        string s;
        cin >> r >> c >> t >> s;
        r--;
        c--;
        ItemBox box;
        box.type = t;
        box.name = s;
        item_boxes[{r, c}] = box;
    }
    processGame();
    outputResult();
    return 0;
}
