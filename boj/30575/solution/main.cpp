#include <bits/stdc++.h>
using namespace std;

/*
 Expressions (Baekjoon 30575)

 N개의 수와 (N-1)개의 연산자('+', '-', '*')가 주어짐.
 곱셈은 덧셈/뺄셈보다 우선순위가 높으며, 최종 식의 홀수/짝수만 판단하면 됨.

 입력
 1) 첫 줄: N, M (1 ≤ N, M ≤ 10^5)
 2) 둘째 줄: 2N-1개 토큰 (Ai, op_i, Ai+1, ... 형태)
    - Ai (1 ≤ Ai ≤ 10^9)
    - op_i ∈ {'+', '-', '*'}
 3) 이후 M줄: "X Y" 형태
    - X번째 숫자를 Y로 변경 (1 ≤ X ≤ N, 1 ≤ Y ≤ 10^9)

 출력
 - 총 M+1줄
 - i번째 줄: i-1번째 변경까지 반영된 식의 결과가 짝수이면 "even", 홀수이면 "odd"
   (i=1은 아직 변경 전 상태)
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // 토큰을 받을 임시 벡터 (숫자와 연산이 섞여 있으므로 크기는 2N-1)
    // 인덱스 짝수: 숫자 (0-based 가정 시)
    // 인덱스 홀수: 연산자
    vector<string> tokens(2 * N - 1);
    for (int i = 0; i < 2 * N - 1; i++) {
        cin >> tokens[i];
    }

    // numbers[i] = i번째(1-based) 수의 홀짝 (0=even, 1=odd)
    // 편의를 위해 0-based로 관리할 수도 있지만 문제 설명에서 X번째 수 등으로 활용
    vector<int> numbers(N);

    // 연산자 배열 (크기 N-1)
    // ops[i] = tokens[2*i + 1] (i = 0 ~ N-2)
    vector<char> ops(N - 1);

    // numbers/ops 파싱
    for (int i = 0; i < N; i++) {
        long long val = stoll(tokens[2 * i]);  // 2*i 번째 토큰은 숫자
        numbers[i] = (val % 2 == 0) ? 0 : 1;
    }
    for (int i = 0; i < N - 1; i++) {
        ops[i] = tokens[2 * i + 1][0];  // 2*i+1 번째 토큰은 연산자
    }

    // 곱셈(*)으로 이어진 구간을 하나의 덩어리(=term)로 묶는다.
    // term_index[i] = i번째 수가 속한 term의 인덱스
    // 예: 11 + 22 * 33 - 44 * 55 * 66
    //     term 분할 → (11) , (22 * 33), (44 * 55 * 66)  총 3개
    vector<int> term_index(N, 0);
    int t_idx = 0;
    term_index[0] = 0;
    for (int i = 0; i < N - 1; i++) {
        if (ops[i] == '*') {
            // 같은 term
            term_index[i + 1] = t_idx;
        } else {
            // '+', '-'는 새 term
            t_idx++;
            term_index[i + 1] = t_idx;
        }
    }
    int term_count = t_idx + 1;  // 전체 덩어리 개수

    // 각 term에 대해 "짝수의 개수"를 센다.
    // 짝수 개수 > 0 이면 그 term의 값 = 0
    // 짝수 개수 = 0 이면 그 term의 값 = 1
    vector<int> evenCountInTerm(term_count, 0);

    for (int i = 0; i < N; i++) {
        if (numbers[i] == 0) {  // 짝수라면
            evenCountInTerm[term_index[i]]++;
        }
    }

    // 각 term의 현재 값 (mod 2) 및 전체 XOR
    // termValue[i] = (evenCountInTerm[i] == 0) ? 1 : 0
    // 전체 parity = (모든 termValue의 XOR)
    int global_parity = 0;
    for (int i = 0; i < term_count; i++) {
        int val = (evenCountInTerm[i] == 0) ? 1 : 0;
        global_parity ^= val;
    }

    auto printAnswer = [&](int parity) {
        cout << (parity == 0 ? "even\n" : "odd\n");
    };

    // 아직 변경 전 상태의 식의 결과
    printAnswer(global_parity);

    // 업데이트 처리를 위한 람다
    auto updateValue = [&](int idx, long long newVal) {
        // idx번째 수가 바뀌기 전/후의 홀짝 비교
        // numbers[idx] : 기존 홀짝 (0=짝수, 1=홀수)
        int oldParity = numbers[idx];
        int newParity = (newVal % 2 == 0) ? 0 : 1;
        if (oldParity == newParity) return;  // 바뀌지 않으면 아무것도 안 함

        // 덩어리 식별
        int t = term_index[idx];
        // 1) 만약 기존 값이 짝수였다면, 그 term의 evenCountInTerm[t]를 하나 줄임
        // 2) 새 값이 짝수면 evenCountInTerm[t]를 하나 늘림
        if (oldParity == 0) {
            // 짝수 → 홀수로 변경
            evenCountInTerm[t]--;
            // 혹시 이로 인해 term의 값이 0→1로 바뀔 수 있음
            if (evenCountInTerm[t] == 0) {
                // term 값 0->1
                global_parity ^= 1;
            }
        } else {
            // 홀수 → 짝수로 변경
            evenCountInTerm[t]++;
            // 혹시 이로 인해 term의 값이 1->0으로 바뀔 수 있음
            if (evenCountInTerm[t] == 1) {
                // term 값 1->0
                global_parity ^= 1;
            }
        }
        numbers[idx] = newParity;
    };

    // M번 업데이트
    while (M--) {
        long long X, Y;
        cin >> X >> Y;
        // 문제에서 X는 1-based
        updateValue(X - 1, Y);

        // 업데이트 후 결과 출력
        printAnswer(global_parity);
    }

    return 0;
}
