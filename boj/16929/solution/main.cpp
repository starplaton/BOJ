#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<string> grid;
vector<vector<bool>> visited;

// Directions: up, down, left, right
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// DFS function to detect cycle
bool dfs(int x, int y, int from_x, int from_y, char color, int depth) {
    visited[x][y] = true;

    for (int dir = 0; dir < 4; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        // Check bounds
        if (nx < 0 || nx >= N || ny < 0 || ny >= M)
            continue;

        // Check color
        if (grid[nx][ny] != color)
            continue;

        if (!visited[nx][ny]) {
            if (dfs(nx, ny, x, y, color, depth + 1))
                return true;
        } else {
            // If the adjacent cell is visited and not the parent
            if (nx != from_x || ny != from_y) {
                if (depth >= 4)
                    return true;
            }
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    grid.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> grid[i];
    }

    visited.assign(N, vector<bool>(M, false));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!visited[i][j]) {
                if (dfs(i, j, -1, -1, grid[i][j], 1)) {
                    cout << "Yes";
                    return 0;
                }
            }
        }
    }

    cout << "No";
}
