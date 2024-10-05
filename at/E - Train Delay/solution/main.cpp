#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 열차 정보를 저장하는 구조체
struct Train {
    int A;  // 출발 도시
    int B;  // 도착 도시
    ll S;   // 예정 출발 시간
    ll T;   // 예정 도착 시간
};

// 이벤트 정보를 저장하는 구조체
struct Event {
    ll time;       // 이벤트 시간
    int type;      // 0 = 도착, 1 = 출발
    int train_id;  // 열차 번호

    // 정렬 기준: 시간 오름차순, 동일 시간일 경우 도착 이벤트 먼저
    bool operator<(const Event& other) const {
        if (time != other.time)
            return time < other.time;
        return type < other.type;  // 도착 이벤트(0)가 출발 이벤트(1)보다 먼저
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    ll X1;
    cin >> N >> M >> X1;

    // 열차 정보 입력
    vector<Train> trains(M + 1);
    for (int i = 1; i <= M; i++) {
        cin >> trains[i].A >> trains[i].B >> trains[i].S >> trains[i].T;
    }

    // 모든 이벤트 생성
    vector<Event> events;
    events.reserve(2 * M);
    for (int i = 1; i <= M; i++) {
        events.push_back(Event{trains[i].T, 0, i});  // 도착 이벤트
        events.push_back(Event{trains[i].S, 1, i});  // 출발 이벤트
    }

    // 이벤트 정렬
    sort(events.begin(), events.end());

    // 각 열차의 지연 시간 초기화 (1번 열차는 주어진 X1으로 설정)
    vector<ll> X(M + 1, 0);
    X[1] = X1;

    // 각 도시의 최신 실제 도착 시간 초기화
    vector<ll> latest_arrival(N + 1, 0);

    // 이벤트 순서대로 처리
    for (auto& e : events) {
        if (e.type == 0) {
            // 도착 이벤트 처리
            int c = trains[e.train_id].B;
            ll actual_arrival = trains[e.train_id].T + X[e.train_id];
            latest_arrival[c] = max(latest_arrival[c], actual_arrival);
        } else {
            // 출발 이벤트 처리
            int c = trains[e.train_id].A;
            if (e.train_id == 1) {
                // 1번 열차는 지연 시간이 고정되어 있으므로 아무 작업도 하지 않음
                continue;
            } else {
                // 필요한 최소 지연 시간 계산
                ll required_Xi = max(latest_arrival[c] - trains[e.train_id].S, (ll)0);
                X[e.train_id] = required_Xi;
            }
        }
    }

    // 결과 출력: X2부터 XM까지
    for (int i = 2; i <= M; i++) {
        cout << X[i];
        if (i != M) cout << " ";
    }
    cout << "\n";
}
