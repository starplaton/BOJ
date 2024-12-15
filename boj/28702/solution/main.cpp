#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 입력: 세 개의 FizzBuzz 출력
    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;

    // 슬라이딩 윈도우 초기화
    deque<string> window;

    const int MAX_I = 100'000'000;

    for (int i = 1; i <= MAX_I; ++i) {
        string current;
        if (i % 15 == 0) {
            current = "FizzBuzz";
        } else if (i % 3 == 0) {
            current = "Fizz";
        } else if (i % 5 == 0) {
            current = "Buzz";
        } else {
            current = to_string(i);
        }

        if (window.size() == 3) {
            // 현재 윈도우가 입력된 세 개의 문자열과 일치하는지 확인
            if (window[0] == s1 && window[1] == s2 && window[2] == s3) {
                // 일치하면 현재 출력이 다음 출력
                cout << current;
                return 0;
            }
            // 슬라이딩 윈도우 업데이트: 맨 앞 제거
            window.pop_front();
        }
        // 현재 출력을 윈도우에 추가
        window.push_back(current);
    }

    // 문제의 조건에 따라 항상 일치하는 경우가 존재하므로,
    // 여기 도달하지 않아야 함. 그러나 안전을 위해 추가
    // 출력 (예: 없음)
    cout << "No solution found";
    return 0;
}
