#include <bits/stdc++.h>
using namespace std;

// 문자를 숫자로 매핑하기 위한 헬퍼
int toInt(char c) {
    if (c == 'S') return 0;  // 해
    if (c == 'R') return 1;  // 강
    return 2;                // W: 바람
}

// 원래 문자를 바꿀 필요가 있는지 체크 (같으면 0, 다르면 1)
inline int mismatchCost(int originalType, int newType) {
    return (originalType == newType ? 0 : 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, H;
    cin >> N >> H;
    string S;
    cin >> S;

    // S를 정수 배열로 변환
    vector<int> veins(N);
    for (int i = 0; i < N; i++) {
        veins[i] = toInt(S[i]);
    }

    // 1) H=1 -> 아무 제약 없음 -> 전부 다 잡힘 -> 변환 0번
    if (H == 1) {
        cout << 0 << "\n";
        return 0;
    }

    // 2) H=2 -> 인접한 칸끼리 다른 색이어야 함
    //    3색 중 하나를 골라서, i-1과 달라야 함.
    if (H == 2) {
        // dp[i][c] = i번 칸을 색 c로 칠했을 때, 0..i까지 최소 치환비용
        // c는 {0,1,2} (S,R,W)
        // 점화식: dp[i][c] = min( dp[i-1][p] ) + mismatchCost(veins[i], c), 단 p != c
        vector<vector<int>> dp(N, vector<int>(3, 1e9));
        // 초기값
        for (int c = 0; c < 3; c++) {
            dp[0][c] = mismatchCost(veins[0], c);
        }
        // 채우기
        for (int i = 1; i < N; i++) {
            for (int c = 0; c < 3; c++) {
                int costHere = mismatchCost(veins[i], c);
                int bestPrev = 1e9;
                for (int p = 0; p < 3; p++) {
                    if (p == c) continue;  // 인접 불가
                    bestPrev = min(bestPrev, dp[i - 1][p]);
                }
                dp[i][c] = bestPrev + costHere;
            }
        }
        // 답: 마지막 칸에 가능한 색 3가지 중 최솟값
        int ans = min({dp[N - 1][0], dp[N - 1][1], dp[N - 1][2]});
        cout << ans << "\n";
        return 0;
    }

    // 3) H=3 -> T_i != T_{i+1}, T_i != T_{i+2}
    //    즉, i와 i+1이 다른 색, i와 i+2도 다른 색
    //    dp[i][c][p] = i번 칸을 c색, i-1번 칸을 p색이라 했을 때의 최소 비용
    //    다만 T_i != T_{i-1} (=p), T_i != T_{i-2} => i-2 색은 dp 이전 단계에서 p를 정할 때 이미 알 수 있어야 함
    //    편의상 i-2 색을 q라 하면 dp[i-1][p][q] 상태에서 i색 c를 정해나가는 식으로 가능

    if (H == 3) {
        // dp[i][c][p] : i번째 색 c, (i-1)번째 색 p
        // => 여기서 (i-2)번째 색 q != c 여야 함 (또한 p != c).
        static int dp[1000001][3][3];
        const int INF = 1000000000;
        // 전부 INF로 초기화
        for (int i = 0; i <= N; i++) {
            for (int c = 0; c < 3; c++) {
                for (int p = 0; p < 3; p++) {
                    dp[i][c][p] = INF;
                }
            }
        }

        // i=0 초기화
        // dp[0][c][?] 라고 하면, 사실 p는 의미 없으니 임의로 dp[0][c][0] 등으로 넣어둘 수 있음
        for (int c = 0; c < 3; c++) {
            dp[0][c][0] = mismatchCost(veins[0], c);
        }

        // i=1 갱신
        for (int c = 0; c < 3; c++) {
            for (int p = 0; p < 3; p++) {
                if (c == p) continue;  // 인접 불가
                // i=1에서 c, i=0에서 p
                // dp[1][c][p] = dp[0][p][x] + mismatch(1,c) (x는 상관없는 더미)
                int cost = mismatchCost(veins[1], c);
                for (int x = 0; x < 3; x++) {
                    // dp[0][p][x]가 유효한 경우만
                    if (dp[0][p][x] == INF) continue;
                    dp[1][c][p] = min(dp[1][c][p], dp[0][p][x] + cost);
                }
            }
        }

        // i=2..N-1 일반 케이스
        for (int i = 2; i < N; i++) {
            for (int c = 0; c < 3; c++) {      // 현재 색
                for (int p = 0; p < 3; p++) {  // 바로 직전 색
                    if (c == p) continue;      // i-1과 달라야
                    // i-2 색(q)도 c와 달라야
                    int costC = mismatchCost(veins[i], c);
                    for (int q = 0; q < 3; q++) {
                        if (dp[i - 1][p][q] == INF) continue;
                        if (q == c) continue;  // i-2 색과 현재 색이 같으면 안 됨
                        // 유효
                        int newCost = dp[i - 1][p][q] + costC;
                        if (newCost < dp[i][c][p]) {
                            dp[i][c][p] = newCost;
                        }
                    }
                }
            }
        }

        // 답: dp[N-1][c][p] 중 최솟값
        int ans = INT_MAX;
        if (N == 1) {
            // N=1인 경우엔 dp[0][c][0] 중 최솟값
            for (int c = 0; c < 3; c++) {
                ans = min(ans, dp[0][c][0]);
            }
        } else if (N == 2) {
            // N=2인 경우 dp[1][c][p] 중 최솟값
            for (int c = 0; c < 3; c++) {
                for (int p = 0; p < 3; p++) {
                    ans = min(ans, dp[1][c][p]);
                }
            }
        } else {
            for (int c = 0; c < 3; c++) {
                for (int p = 0; p < 3; p++) {
                    ans = min(ans, dp[N - 1][c][p]);
                }
            }
        }

        cout << ans << "\n";
        return 0;
    }

    // 4) H >= 4
    //    - N>3 이면 색이 3개뿐이라 불가능(-1).
    //    - N<=3 이면 최대 3^3=27 경우를 전부 확인해볼 수 있음.
    if (H >= 4) {
        if (N > 3) {
            cout << -1 << "\n";
            return 0;
        }
        // N이 1,2,3일 때 가능한 모든 3^N 배치 시도
        // 조건: 모든 i < j 에 대해, (j - i) < H => 즉 (j - i)=1,2,3 에는 같은 색 금지
        // N 최대 3이면 (j-i) 가능값은 1,2(또는 3). H>=4이므로 1,2,3 다 <4 => 전부 금지
        // 결국 N=3 이면 세 칸 모두 서로 달라야 함, N=2면 두 칸 달라야 함, N=1이면 아무거나.
        int best = INT_MAX;
        int limit = 1;
        for (int i = 0; i < N; i++) limit *= 3;  // 3^N

        for (int mask = 0; mask < limit; mask++) {
            // mask를 3진수로 풀어서 color[i]를 얻음
            vector<int> color(N);
            int tmp = mask;
            for (int i = 0; i < N; i++) {
                color[i] = tmp % 3;
                tmp /= 3;
            }
            // 조건 검사
            bool valid = true;
            for (int i = 0; i < N; i++) {
                for (int j = i + 1; j < N; j++) {
                    if ((j - i) < H && color[i] == color[j]) {
                        valid = false;
                        break;
                    }
                }
                if (!valid) break;
            }
            if (!valid) continue;
            // 비용 계산
            int cost = 0;
            for (int i = 0; i < N; i++) {
                cost += mismatchCost(veins[i], color[i]);
            }
            best = min(best, cost);
        }
        if (best == INT_MAX) best = -1;
        cout << best << "\n";
    }

    return 0;
}
