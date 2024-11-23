#include <bits/stdc++.h>
using namespace std;

// 최대 레벨과 장난감 개수 정의
const int MAX_LEVEL = 10;
const int MAX_TOY = 100;

// 팩토리얼을 저장할 배열
unsigned long long factorials[11];

// 메모이제이션을 위한 배열 크기 계산
const int SIZE = 11 * 101 * 101 * 101;  // level (1-10) * R (0-100) * G (0-100) * B (0-100)
unsigned long long memo_table_arr[11333312];
bool visited_flag_arr_memo[11333312];

// 고유 인덱스를 계산하는 함수
inline int get_index(int level, int r, int g, int b) {
    return level * 101 * 101 * 101 + r * 101 * 101 + g * 101 + b;
}

// DFS 함수 정의
unsigned long long dfs(int N, int level, int r, int g, int b) {
    if (level > N) {
        return 1;
    }

    // 현재 상태의 인덱스 계산
    int index = get_index(level, r, g, b);

    // 이미 계산된 경우 저장된 값을 반환
    if (visited_flag_arr_memo[index]) {
        return memo_table_arr[index];
    }

    // 현재 상태를 방문 처리
    visited_flag_arr_memo[index] = true;

    unsigned long long total = 0;

    // C=1,2,3에 대해 반복
    for (int C = 1; C <= 3; C++) {
        if (level % C != 0) {
            continue;  // C가 level을 나누지 못하면 건너뜀
        }
        int x = level / C;  // 각 색상에 배치할 장난감 수

        if (C == 1) {
            // 단일 색상 배치: R, G, B 중 하나 선택
            if (r >= x) {
                total += dfs(N, level + 1, r - x, g, b);
            }
            if (g >= x) {
                total += dfs(N, level + 1, r, g - x, b);
            }
            if (b >= x) {
                total += dfs(N, level + 1, r, g, b - x);
            }
        } else if (C == 2) {
            // 두 가지 색상 배치: R&G, R&B, G&B
            // R & G
            if (r >= x && g >= x) {
                unsigned long long arrangements = factorials[level] / (factorials[x] * factorials[x]);
                total += arrangements * dfs(N, level + 1, r - x, g - x, b);
            }
            // R & B
            if (r >= x && b >= x) {
                unsigned long long arrangements = factorials[level] / (factorials[x] * factorials[x]);
                total += arrangements * dfs(N, level + 1, r - x, g, b - x);
            }
            // G & B
            if (g >= x && b >= x) {
                unsigned long long arrangements = factorials[level] / (factorials[x] * factorials[x]);
                total += arrangements * dfs(N, level + 1, r, g - x, b - x);
            }
        } else if (C == 3) {
            // 세 가지 색상 배치: R, G, B 모두 사용
            if (r >= x && g >= x && b >= x) {
                unsigned long long arrangements = factorials[level] / (factorials[x] * factorials[x] * factorials[x]);
                total += arrangements * dfs(N, level + 1, r - x, g - x, b - x);
            }
        }
    }

    // 계산된 값을 저장
    memo_table_arr[index] = total;
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, R, G, B;
    cin >> N >> R >> G >> B;

    // 팩토리얼 미리 계산
    factorials[0] = 1;
    for (int i = 1; i <= MAX_LEVEL; i++) {
        factorials[i] = factorials[i - 1] * i;
    }

    // 필요한 총 장난감 수 계산
    int total_needed = N * (N + 1) / 2;
    if (R + G + B < total_needed) {
        cout << "0";
        return 0;
    }

    // 메모이제이션 배열 초기화
    memset(memo_table_arr, 0, sizeof(memo_table_arr));
    memset(visited_flag_arr_memo, 0, sizeof(visited_flag_arr_memo));

    // DFS 시작
    unsigned long long result = dfs(N, 1, R, G, B);

    cout << result;
}
