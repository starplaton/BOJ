#include <iostream>
#include <vector>

using namespace std;

int main() {
    int K;  // 입력 데이터 세트의 수
    cin >> K;

    for (int dataset = 1; dataset <= K; ++dataset) {
        int n, s, d;
        cin >> n >> s >> d;  // 배의 수, 배의 속도, 남은 시간

        int total_ducats = 0;

        // 각 배의 정보를 처리
        for (int i = 0; i < n; ++i) {
            int distance, value;
            cin >> distance >> value;

            // 배가 시간 내에 도착할 수 있으면 화물 가치를 더함
            if (distance <= s * d) {
                total_ducats += value;
            }
        }

        // 출력
        cout << "Data Set " << dataset << ":\n";
        cout << total_ducats << "\n\n";
    }

    return 0;
}
