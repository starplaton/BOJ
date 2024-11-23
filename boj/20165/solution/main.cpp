#include <bits/stdc++.h>
using namespace std;

// 방향 매핑: N, S, E, W
const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

// 함수: 방향 문자를 인덱스로 변환
int dirToIndex(char D) {
    if (D == 'N') return 0;
    if (D == 'S') return 1;
    if (D == 'E') return 2;
    if (D == 'W') return 3;
    return -1;  // 에러
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, R;
    cin >> N >> M >> R;

    // 도미노 높이 저장
    vector<vector<int>> heights(N, vector<int>(M, 0));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> heights[i][j];
        }
    }

    // 도미노 상태 저장: 'S' 또는 'F'
    vector<vector<char>> state(N, vector<char>(M, 'S'));

    long long total_score = 0;

    // R 라운드 처리
    for (int round = 0; round < R; ++round) {
        // 공격수의 행동
        int X, Y;
        char D;
        cin >> X >> Y >> D;
        // 1-based에서 0-based로 변환
        int r = X - 1;
        int c = Y - 1;
        int dir = dirToIndex(D);

        // BFS를 위한 큐
        queue<pair<int, int>> q;
        // 넘어뜨릴 도미노가 서 있는지 확인
        if (state[r][c] == 'S') {
            q.push({r, c});
        }

        int count = 0;
        while (!q.empty()) {
            pair<int, int> current = q.front();
            q.pop();
            int cr = current.first;
            int cc = current.second;
            if (state[cr][cc] == 'F') continue;
            // 도미노를 넘어뜨림
            state[cr][cc] = 'F';
            count++;
            int K = heights[cr][cc];
            // 방향에 따라 이동
            for (int step = 1; step < K; ++step) {
                int nr = cr + dr[dir] * step;
                int nc = cc + dc[dir] * step;
                // 범위 확인
                if (nr < 0 || nr >= N || nc < 0 || nc >= M) break;
                if (state[nr][nc] == 'S') {
                    q.push({nr, nc});
                }
            }
        }
        // 공격수의 점수에 합산
        total_score += count;

        // 수비수의 행동
        cin >> X >> Y;
        r = X - 1;
        c = Y - 1;
        if (state[r][c] == 'F') {
            state[r][c] = 'S';
        }
    }

    // 결과 출력
    cout << total_score << "\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cout << (state[i][j] == 'F' ? 'F' : 'S');
            if (j != M - 1) cout << ' ';
        }
        cout << '\n';
    }
}
