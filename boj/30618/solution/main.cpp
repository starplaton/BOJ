#include <bits/stdc++.h>
using namespace std;

// 구조체를 이용하여 위치와 가중치를 저장
struct Position {
    long long weight;
    int pos;
};

// 비교 함수: 가중치가 큰 순으로 정렬
bool compare(const Position &a, const Position &b) {
    if (a.weight != b.weight)
        return a.weight > b.weight;
    return a.pos < b.pos;  // 가중치가 같을 경우 위치가 작은 것을 먼저
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    // 모든 위치의 가중치를 계산하여 벡터에 저장
    vector<Position> positions;
    positions.reserve(N);
    for (int k = 1; k <= N; ++k) {
        long long w = (long long)k * (N - k + 1);
        positions.push_back(Position{w, k});
    }

    // 가중치 기준으로 내림차순 정렬
    sort(positions.begin(), positions.end(), compare);

    // 순열을 저장할 벡터 초기화 (1-based index)
    vector<int> permutation(N + 1, 0);

    // 가장 큰 수부터 가중치가 큰 위치에 할당
    int current_number = N;
    for (auto &p : positions) {
        permutation[p.pos] = current_number;
        current_number--;
    }

    // 결과 출력
    for (int k = 1; k <= N; ++k) {
        cout << permutation[k] << (k == N ? '\n' : ' ');
    }
}
