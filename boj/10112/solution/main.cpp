#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 구조체를 사용하여 행성을 관리
struct Planet {
    int A;  // 얻을 수 있는 연료
    int B;  // 이동 비용
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, P;
    cin >> N >> P;

    vector<Planet> planets(N);
    for (int i = 0; i < N; i++) cin >> planets[i].A >> planets[i].B;

    // 시작 행성 인덱스 (1-based to 0-based)
    int start = P - 1;

    // 초기 연료는 시작 행성의 연료
    ll current_fuel = planets[start].A;

    // 시작 행성을 제외한 나머지 행성들 리스트 생성
    vector<pair<int, int>> other_planets;
    other_planets.reserve(N - 1);
    for (int i = 0; i < N; i++) {
        if (i != start) {
            other_planets.emplace_back(planets[i].B, planets[i].A);
        }
    }

    // 이동 비용 B_i 기준으로 오름차순 정렬
    sort(other_planets.begin(), other_planets.end());

    // 우선순위 큐 (Max Heap), (A_i - B_i, A_i)
    priority_queue<pair<int, int>> pq;

    // 행성을 순회할 포인터
    int ptr = 0;

    // 최종 연료와 방문한 행성 수 초기화
    ll max_fuel = current_fuel;
    ll visited = 1;  // 시작 행성 방문

    while (true) {
        // 현재 연료로 이동 가능한 모든 행성을 우선순위 큐에 추가
        while (ptr < other_planets.size() && other_planets[ptr].first <= current_fuel) {
            int B = other_planets[ptr].first;
            int A = other_planets[ptr].second;
            pq.emplace(A - B, A);
            ptr++;
        }

        // 우선순위 큐가 비어있으면 더 이상 이동 불가
        if (pq.empty()) break;

        // 가장 큰 (A_i - B_i) 값을 가진 행성 선택
        pair<int, int> top = pq.top();
        pq.pop();

        int delta = top.first;
        int A_i = top.second;

        // (A_i - B_i) >=0 인 경우만 채굴
        if (delta < 0) {
            break;
        }

        // 채굴 수행
        current_fuel += delta;
        visited++;

        // 최종 연료와 방문한 행성 수 업데이트
        if (current_fuel > max_fuel) {
            max_fuel = current_fuel;
        }
        // 같은 연료일 때는 방문한 행성 수를 최대화하려면 이미 최대화된 상태임

        // 다음 루프에서 새로운 행성이 추가될 수 있음
    }

    // 추가적으로, 채굴한 후에도 같은 연료로 더 많은 행성을 채굴할 수 있는지 확인
    // 하지만 이미 (A_i - B_i) >=0인 행성들만 채굴했으므로, 추가로 불리한 행성은 무시

    // 최종 결과 출력
    cout << max_fuel << "\n"
         << visited;

    return 0;
}
