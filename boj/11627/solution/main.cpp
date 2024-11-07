#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_W = 1000;
const int MAX_L = 1000;

struct Position {
    int x, y, time;
};

struct GodzillaState {
    int x, y;
    int destroyedResidential;
};

int dx[4] = {0, 1, 0, -1}; // N, E, S, W
int dy[4] = {-1, 0, 1, 0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int L, W;
        cin >> L >> W;

        vector<string> grid(W);
        for (int i = 0; i < W; ++i) {
            cin >> grid[i];
        }

        // Initialize map and positions
        vector<vector<char>> map(W, vector<char>(L));
        vector<vector<bool>> godzillaVisited(W, vector<bool>(L, false));
        vector<vector<int>> mechVisitedTime(W, vector<int>(L, -1));

        int godzillaX, godzillaY;
        vector<Position> mechs;

        for (int y = 0; y < W; ++y) {
            for (int x = 0; x < L; ++x) {
                map[y][x] = grid[y][x];

                if (map[y][x] == 'G') {
                    godzillaX = x;
                    godzillaY = y;
                    map[y][x] = '.'; // Godzilla's starting position is non-residential
                } else if (map[y][x] == 'M') {
                    mechs.push_back({x, y, 0});
                    map[y][x] = '.'; // Mech's starting position is non-residential
                    mechVisitedTime[y][x] = 0;
                }
            }
        }

        // Simulate Godzilla's movement
        vector<GodzillaState> godzillaStates;
        godzillaStates.push_back({godzillaX, godzillaY, 0});

        vector<vector<bool>> godzillaVisitedMap(W, vector<bool>(L, false));
        godzillaVisitedMap[godzillaY][godzillaX] = true;

        vector<vector<char>> currentMap = map; // Copy of the map to update during simulation

        int maxTime = W * L; // Maximum possible time

        for (int t = 0; t < maxTime; ++t) {
            if (t >= godzillaStates.size()) {
                // Godzilla has stopped moving
                break;
            }

            GodzillaState gState = godzillaStates[t];
            int gx = gState.x;
            int gy = gState.y;
            int destroyed = gState.destroyedResidential;

            // Determine Godzilla's next move
            int nextX = gx, nextY = gy;
            bool moved = false;

            // First, check for adjacent residential sectors (N, E, S, W)
            for (int dir = 0; dir < 4; ++dir) {
                int nx = gx + dx[dir];
                int ny = gy + dy[dir];

                if (nx >= 0 && nx < L && ny >= 0 && ny < W) {
                    if (currentMap[ny][nx] == 'R') {
                        // Move to residential sector and destroy it
                        nextX = nx;
                        nextY = ny;
                        destroyed += 1;
                        currentMap[ny][nx] = '.'; // Turn into ruined sector
                        godzillaVisitedMap[ny][nx] = true;
                        moved = true;
                        break;
                    }
                }
            }

            if (!moved) {
                // No adjacent residential sector, try to move to unvisited sector (N, E, S, W)
                for (int dir = 0; dir < 4; ++dir) {
                    int nx = gx + dx[dir];
                    int ny = gy + dy[dir];

                    if (nx >= 0 && nx < L && ny >= 0 && ny < W) {
                        if (!godzillaVisitedMap[ny][nx]) {
                            // Move to unvisited sector
                            nextX = nx;
                            nextY = ny;
                            godzillaVisitedMap[ny][nx] = true;
                            moved = true;
                            break;
                        }
                    }
                }
            }

            if (!moved) {
                // Godzilla cannot move, stays put
                nextX = gx;
                nextY = gy;
            }

            // Record Godzilla's next state
            godzillaStates.push_back({nextX, nextY, destroyed});
        }

        // BFS for mechs
        queue<Position> mechQueue;
        for (const auto& mech : mechs) {
            mechQueue.push(mech);
        }

        int result = -1; // Number of residential sectors destroyed

        while (!mechQueue.empty()) {
            Position mPos = mechQueue.front();
            mechQueue.pop();

            int mx = mPos.x;
            int my = mPos.y;
            int mTime = mPos.time;

            if (mTime >= godzillaStates.size()) {
                continue;
            }

            int gx = godzillaStates[mTime].x;
            int gy = godzillaStates[mTime].y;

            // Check if mech can fire at Godzilla at time mTime
            if (mx == gx || my == gy) {
                bool canFire = true;

                if (mx == gx) {
                    int minY = min(my, gy);
                    int maxY = max(my, gy);
                    for (int y = minY + 1; y < maxY; ++y) {
                        if (currentMap[y][mx] == 'R') {
                            canFire = false;
                            break;
                        }
                    }
                } else {
                    int minX = min(mx, gx);
                    int maxX = max(mx, gx);
                    for (int x = minX + 1; x < maxX; ++x) {
                        if (currentMap[my][x] == 'R') {
                            canFire = false;
                            break;
                        }
                    }
                }

                if (canFire) {
                    // Mech can fire at Godzilla
                    result = godzillaStates[mTime].destroyedResidential;
                    break;
                }
            }

            // Expand mech's movement
            for (int dir = 0; dir < 4; ++dir) {
                int nx = mx + dx[dir];
                int ny = my + dy[dir];

                if (nx >= 0 && nx < L && ny >= 0 && ny < W) {
                    if (currentMap[ny][nx] != 'R' && mechVisitedTime[ny][nx] == -1) {
                        mechVisitedTime[ny][nx] = mTime + 1;
                        mechQueue.push({nx, ny, mTime + 1});
                    }
                }
            }
        }

        cout << result << '\n';
    }

    return 0;
}
