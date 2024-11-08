#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// 경로가 교차하는지 확인하는 함수
bool isCrossing(int start1, int end1, int start2, int end2) {
    return (start1 < start2 && start2 < end1 && end1 < end2) ||
           (start2 < start1 && start1 < end2 && end2 < end1);
}

int main() {
    string path;
    cin >> path;

    // 각 소의 처음과 두 번째 출현 위치를 저장할 배열
    vector<pair<int, int>> positions(26, {-1, -1});

    // 각 소의 위치 기록
    for (int i = 0; i < path.size(); i++) {
        int cow = path[i] - 'A';
        if (positions[cow].first == -1)
            positions[cow].first = i;  // 첫 번째 위치 기록
        else
            positions[cow].second = i;  // 두 번째 위치 기록
    }

    int crossingPairs = 0;

    // 모든 소 쌍에 대해 교차 여부 확인
    for (int i = 0; i < 26; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (isCrossing(positions[i].first, positions[i].second, positions[j].first, positions[j].second)) {
                crossingPairs++;
            }
        }
    }

    cout << crossingPairs << endl;
    return 0;
}
