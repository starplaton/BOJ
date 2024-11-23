#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    // 광고판의 빛의 세기를 저장할 배열
    vector<int> A(N);
    for (auto &x : A) cin >> x;

    // 슬라이딩 윈도우를 위한 deque를 배열로 구현
    vector<int> dq(N);
    int head = 0, tail = 0;

    int W = 2 * M - 1;  // 윈도우 크기

    // 결과를 저장할 벡터
    vector<int> results;
    results.reserve(N);

    for (int i = 0; i < N; i++) {
        // 현재 광고판보다 밝기가 낮거나 같은 광고판은 deque에서 제거
        while (head < tail && A[dq[tail - 1]] <= A[i]) tail--;
        dq[tail++] = i;

        // 윈도우 범위를 벗어난 광고판은 deque에서 제거
        while (head < tail && dq[head] < i - W + 1) head++;

        // 윈도우가 완전히 형성되면 최대값을 결과에 추가
        if (i >= W - 1) {
            results.push_back(A[dq[head]]);
        }
    }

    // 결과 출력
    for (int i = 0; i < results.size(); i++) {
        if (i > 0) cout << ' ';
        cout << results[i];
    }
    cout << '\n';
}
