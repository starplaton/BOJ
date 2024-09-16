#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int N;  // 펼쳐질 카드의 개수
    cin >> N;

    vector<pair<string, int>> cards(N);  // 카드 정보 저장 벡터
    for (int i = 0; i < N; ++i) {
        cin >> cards[i].first >> cards[i].second;  // 시계 종류와 시각 입력 받기
    }

    int current_time = 1;  // 현재 시각을 1시로 시작
    int direction = 1;     // 시간 흐름 방향 (1: 증가, -1: 감소)

    for (int i = 0; i < N; ++i) {
        string clock_type = cards[i].first;
        int card_time = cards[i].second;

        bool sync_rule = (current_time == card_time);     // 동기화의 법칙 적용 여부
        bool reverse_rule = (clock_type == "HOURGLASS");  // 시간 역행의 법칙 적용 여부

        if (sync_rule && reverse_rule) {
            // 과부하의 원칙: 두 법칙이 동시에 발동되면 아무것도 하지 않음
            cout << current_time << " NO" << endl;
        } else if (sync_rule) {
            // 동기화의 법칙만 적용
            cout << current_time << " YES" << endl;
        } else if (reverse_rule) {
            // 시간 역행의 법칙만 적용
            cout << current_time << " NO" << endl;
            direction = -direction;  // 시간의 흐름을 반전
        } else {
            // 아무 법칙도 적용되지 않음
            cout << current_time << " NO" << endl;
        }

        // 다음 시각으로 진행
        current_time += direction;
        if (current_time > 12) current_time = 1;  // 12시를 넘으면 1시로 돌아감
        if (current_time < 1) current_time = 12;  // 1시 아래로 내려가면 12시로 돌아감
    }

    return 0;
}
