#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 무한대를 의미하는 값 설정
const ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    // 이동 시간 저장
    vector<vector<int>> grid(N + 1, vector<int>(M + 1, 0));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> grid[i][j];
        }
    }

    // 거리 배열과 목적지 배열 초기화
    vector<vector<ll>> dist(N + 1, vector<ll>(M + 1, INF));
    vector<vector<int>> dest(N + 1, vector<int>(M + 1, -1));

    // 우선순위 큐 (거리, (i,j))
    priority_queue<pair<ll, pair<int, int>>, vector<pair<ll, pair<int, int>>>, std::greater<pair<ll, pair<int, int>>>> pq;

    // 모든 결승선 지점을 시작점으로 초기화
    for (int k = 1; k <= N; k++) {
        dist[k][M] = 0;
        dest[k][M] = k;
        pq.push({0, {k, M}});
    }

    // 상하좌우 이동 방향
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    // 다익스트라 알고리즘 수행
    while (!pq.empty()) {
        auto current = pq.top();
        pq.pop();

        ll current_dist = current.first;
        int x = current.second.first;
        int y = current.second.second;

        // 현재 거리가 이미 더 짧게 설정된 경우 무시
        if (current_dist > dist[x][y]) {
            continue;
        }

        // 인접한 네 방향으로 이동
        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            // 격자판을 벗어나지 않도록 확인
            if (nx < 1 || nx > N || ny < 1 || ny > M) {
                continue;
            }

            ll new_dist = current_dist + grid[nx][ny];

            // 새로운 거리가 기존보다 짧으면 업데이트
            if (new_dist < dist[nx][ny]) {
                dist[nx][ny] = new_dist;
                dest[nx][ny] = dest[x][y];
                pq.push({new_dist, {nx, ny}});
            }
        }
    }

    // 각 결승선 지점에 도착하는 학생 수를 저장할 배열
    vector<int> count(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        // 각 학생의 출발점 (i,1)에서 도착하는 결승선 지점
        int finish_k = dest[i][1];
        if (finish_k != -1) {
            count[finish_k]++;
        }
    }

    // 결과 출력
    for (int k = 1; k <= N; k++) {
        cout << count[k] << "\n";
    }

    return 0;
}
