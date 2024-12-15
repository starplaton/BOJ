#include <cstring>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

const int MAX = 2000;
int n, m;
int grid[MAX][MAX];
int visited[MAX][MAX];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool in_bounds(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

pair<int, int> bfs(vector<pair<int, int>>& fire_starts) {
    queue<pair<int, int>> q;
    memset(visited, 1e9, sizeof(visited));  // 매우 큰 값으로 초기화 (도달 불가능 표시)

    // Initialize BFS
    for (auto& fire : fire_starts) {
        int x = fire.first, y = fire.second;
        q.push({x, y});
        visited[x][y] = 0;  // Start time is 0
    }

    int max_time = 0, total_size = 0;

    while (!q.empty()) {
        int x, y;
        tie(x, y) = q.front();
        q.pop();
        total_size++;

        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (in_bounds(nx, ny) && grid[nx][ny] == 1 && visited[nx][ny] > visited[x][y] + 1) {
                visited[nx][ny] = visited[x][y] + 1;
                max_time = max(max_time, visited[nx][ny]);
                q.push({nx, ny});
            }
        }
    }

    return {max_time, total_size};
}

int main() {
    cin >> n >> m;
    vector<pair<int, int>> fire_starts;
    for (int i = 0; i < n; ++i) {
        string line;
        cin >> line;
        for (int j = 0; j < m; ++j) {
            grid[i][j] = line[j] - '0';
            if (grid[i][j] == 0) {
                fire_starts.push_back({i, j});  // Initial fire positions
            }
        }
    }

    if (fire_starts.empty()) {
        cout << "0 0" << endl;
        return 0;
    }

    auto result = bfs(fire_starts);
    cout << result.first << " " << result.second << endl;
    return 0;
}
