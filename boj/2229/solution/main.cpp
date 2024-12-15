#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    // 학생들의 점수를 1부터 N까지 저장 (1-based indexing)
    vector<int> scores(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        cin >> scores[i];
    }

    // DP 배열 초기화
    // dp[i]는 첫 번째 학생부터 i번째 학생까지 고려했을 때의 최대 "잘 짜여진 정도"의 합
    vector<long long> dp(N + 1, 0);
    dp[0] = 0;  // 초기 상태

    for (int i = 1; i <= N; ++i) {
        int current_max = scores[i];
        int current_min = scores[i];
        dp[i] = 0;  // 최소값은 0

        for (int k = i; k >= 1; --k) {
            current_max = max(current_max, scores[k]);
            current_min = min(current_min, scores[k]);
            dp[i] = max(dp[i], dp[k - 1] + (long long)(current_max - current_min));
        }
    }

    // 결과 출력
    cout << dp[N];

    return 0;
}
