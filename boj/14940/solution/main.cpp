#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 상하좌우 이동을 위한 배열
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // 지도 입력 받기
    vector<vector<int>> map(n, vector<int>(m));
    // 거리를 저장할 배열
    vector<vector<int>> dist(n, vector<int>(m, -1));

    int start_x, start_y;
    // 지도 입력 및 목표지점 찾기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
            if (map[i][j] == 2) {
                start_x = i;
                start_y = j;
            }
            if (map[i][j] == 0) {
                dist[i][j] = 0;  // 갈 수 없는 땅은 0으로 초기화
            }
        }
    }

    // BFS를 위한 큐
    queue<pair<int, int>> q;
    q.push({start_x, start_y});
    dist[start_x][start_y] = 0;  // 시작점의 거리는 0

    // BFS 시작
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // 4방향 탐색
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // 범위 체크
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

            // 아직 방문하지 않은 갈 수 있는 땅이면
            if (map[nx][ny] == 1 && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;  // 거리 갱신
                q.push({nx, ny});               // 큐에 추가
            }
        }
    }

    // 결과 출력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << dist[i][j];
            if (j < m - 1) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}