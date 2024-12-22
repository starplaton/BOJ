#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // 입력 받기
    int N;
    long long K;
    cin >> N >> K;

    vector<long long> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    long long min_operations = 0;

    // 완전한 수열을 만들기 위한 연산 계산
    for (int i = 0; i < (N + 1) / 2; ++i) {
        long long left = A[i];
        long long right = A[N - i - 1];

        // 필요한 값의 차이 계산
        long long diff = abs(left - right);

        long long k = min(diff / K + diff % K, (diff / K + 1) + (diff / K + 1) * K - (diff));
        min_operations += k;
    }

    // 결과 출력
    cout << min_operations << endl;

    return 0;
}
