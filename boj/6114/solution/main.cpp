#include <bits/stdc++.h>
using namespace std;

static const int INF = 1000000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T, S, N;
    cin >> T >> S >> N;
    vector<array<int, 3>> lessons(S);  // M_i, L_i, A_i
    for (int i = 0; i < S; i++) {
        cin >> lessons[i][0] >> lessons[i][1] >> lessons[i][2];
    }
    vector<pair<int, int>> slopes(N);  // C_i, D_i
    for (int i = 0; i < N; i++) {
        cin >> slopes[i].first >> slopes[i].second;
    }

    // minTimeForSkill[s] = s 스킬로 내려갈 수 있는 최소 D_i
    // 스킬이 s 이상 필요한 모든 코스 중 최소 D_i를 구한다.
    // 정확히는 C_i ≤ s 인 모든 코스 중 최소 D_i를 구해야 한다.
    // C_i ≤ s 인 코스 중 최솟값을 구하기 위해, 코스를 C_i 기준으로 정렬.
    vector<int> minTimeForSkill(101, INF);
    // 스킬 레벨 1부터 100까지에 대해 가능한 코스의 최소 시간
    // 먼저 C_i 오름차순 정렬
    sort(slopes.begin(), slopes.end(), [](auto &a, auto &b) {
        return a.first < b.first;
    });
    int idx = 0;
    int curMin = INF;
    for (int s = 1; s <= 100; s++) {
        while (idx < N && slopes[idx].first <= s) {
            curMin = min(curMin, slopes[idx].second);
            idx++;
        }
        minTimeForSkill[s] = curMin;
    }

    // 레슨 정보를 M_i 기준으로 묶는다.
    // 한 시간에 여러 레슨이 시작할 수도 있으므로 vector로 관리
    vector<vector<array<int, 2>>> lessonStartAt(T + 1);
    for (auto &ls : lessons) {
        int M = ls[0], L = ls[1], A = ls[2];
        if (M <= T) {
            lessonStartAt[M].push_back({L, A});
        }
    }

    // DP 배열
    // DP[t][skill] = t시간에 skill레벨일 때 가능한 최대 활강 수
    // 음수로 초기화
    static int DP[10001][101];
    for (int i = 0; i <= T; i++) {
        for (int s = 1; s <= 100; s++) {
            DP[i][s] = -1;
        }
    }
    DP[0][1] = 0;  // 시작: 시간0, 스킬1, 활강0회

    for (int t = 0; t <= T; t++) {
        for (int skill = 1; skill <= 100; skill++) {
            if (DP[t][skill] < 0) continue;  // 불가능 상태
            int runs = DP[t][skill];

            // 1. 아무것도 안 하고 기다리기
            if (t + 1 <= T) {
                DP[t + 1][skill] = max(DP[t + 1][skill], runs);
            }

            // 2. 레슨 수강
            // 해당 시간에 시작하는 레슨이 있을 경우
            for (auto &lec : lessonStartAt[t]) {
                int L = lec[0];
                int A = lec[1];
                int endTime = t + L;
                if (endTime <= T) {
                    DP[endTime][A] = max(DP[endTime][A], runs);
                }
            }

            // 3. 스키 활강
            // skill 레벨로 가능한 최소 시간 코스 존재 시
            int d = minTimeForSkill[skill];
            if (d != INF && t + d <= T) {
                DP[t + d][skill] = max(DP[t + d][skill], runs + 1);
            }
        }
    }

    int answer = 0;
    for (int t = 0; t <= T; t++) {
        for (int s = 1; s <= 100; s++) {
            answer = max(answer, DP[t][s]);
        }
    }

    cout << answer << "\n";

    return 0;
}
