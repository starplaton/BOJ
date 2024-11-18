#include <bits/stdc++.h>
using namespace std;

// Digit DP를 위한 메모이제이션
long long dp[20][4][2];

// 숫자 배열
string num;

// Digit DP 함수
// pos: 현재 자리
// cnt: 현재까지 연속된 '6'의 개수
// tight: 현재까지의 숫자가 제한을 받는지 여부
long long solveDP(int pos, int cnt, int tight_flag) {
    if (pos == num.size()) {
        return (cnt >= 3) ? 1 : 0;
    }
    if (dp[pos][cnt][tight_flag] != -1) {
        return dp[pos][cnt][tight_flag];
    }
    int limit = tight_flag ? (num[pos] - '0') : 9;
    long long res = 0;
    for (int digit = 0; digit <= limit; digit++) {
        int new_cnt = (digit == 6) ? cnt + 1 : 0;
        if (new_cnt > 3) new_cnt = 3;  // 최대로 3으로 제한
        int new_tight = tight_flag && (digit == limit) ? 1 : 0;
        res += solveDP(pos + 1, new_cnt, new_tight);
    }
    return dp[pos][cnt][tight_flag] = res;
}

// 주어진 x 이하의 '종말의 수' 개수 계산
long long count666(long long x) {
    num = to_string(x);
    memset(dp, -1, sizeof(dp));
    return solveDP(0, 0, 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long N;
    cin >> N;

    // 이진 탐색 범위 설정
    long long left = 666;
    long long right = 10LL * N;  // 충분히 큰 수로 설정
    long long answer = 0;

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long cnt = count666(mid);
        if (cnt >= N) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << answer;
    return 0;
}
