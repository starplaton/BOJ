#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> row1(n), row2(n);
    unordered_map<int, vector<int>> positions;  // 덤벨 위치 저장

    // 첫 번째 줄 입력
    for (int i = 0; i < n; i++) {
        cin >> row1[i];
        positions[row1[i]].push_back(i);  // 첫 번째 줄에서 위치 저장
    }

    // 두 번째 줄 입력
    for (int i = 0; i < n; i++) {
        cin >> row2[i];
        positions[row2[i]].push_back(i + n);  // 두 번째 줄에서 위치 저장 (인덱스를 다르게 저장하기 위해 i + n 사용)
    }

    int min_weight_to_lift = 1e9;  // 옮겨야 할 가장 가벼운 덤벨 무게 초기화 (충분히 큰 값으로 설정)

    // 덤벨의 쌍에 대해 계산
    for (auto &entry : positions) {
        int weight = entry.first;
        vector<int> &pos = entry.second;

        // 덤벨 쌍이 같은 줄에 있고 인접해 있는지 확인
        if (abs(pos[0] - pos[1]) > 1) {
            // 만약 인접하지 않으면 사이에 다른 덤벨이 있으므로 이 덤벨을 옮겨야 함
            min_weight_to_lift = min(min_weight_to_lift, weight);
        }
    }

    // 결과 출력
    if (min_weight_to_lift == 1e9) {
        cout << 0 << endl;  // 모두 인접해 있으면 0
    } else {
        cout << min_weight_to_lift << endl;  // 옮겨야 할 덤벨 중 가장 가벼운 것 출력
    }

    return 0;
}
