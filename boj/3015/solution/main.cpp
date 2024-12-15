#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<int> heights(N);
    for (int i = 0; i < N; i++) cin >> heights[i];

    ll answer = 0;
    // 스택에는 (높이, 같은 높이의 개수) 형태의 쌍을 저장
    vector<pair<int, int>> stack_pairs;

    for (int i = 0; i < N; i++) {
        int current = heights[i];
        // 현재 사람보다 키가 작은 사람들을 스택에서 제거하고 카운트에 추가
        while (!stack_pairs.empty() && stack_pairs.back().first < current) {
            answer += stack_pairs.back().second;
            stack_pairs.pop_back();
        }
        // 스택의 최상단과 현재 사람의 키가 같은 경우
        if (!stack_pairs.empty() && stack_pairs.back().first == current) {
            int cnt = stack_pairs.back().second;
            answer += cnt;
            // 같은 키를 가진 사람들 아래에 더 높은 사람이 있으면 추가로 하나의 쌍을 더함
            if (stack_pairs.size() > 1) {
                answer += 1;
            }
            // 현재 사람을 스택에 추가
            stack_pairs.back().second += 1;
        } else {
            // 스택에 더 높은 사람이 있으면 하나의 쌍을 더함
            if (!stack_pairs.empty()) {
                answer += 1;
            }
            // 현재 사람을 스택에 추가
            stack_pairs.emplace_back(current, 1);
        }
    }

    cout << answer;
}
