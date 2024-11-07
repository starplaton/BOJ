#include <iostream>
using namespace std;

const int MOD = 987654321;
const int MAX_N = 5000;  // N/2 최대값

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    int n = N / 2;

    long long catalan[MAX_N + 1] = {0};
    catalan[0] = 1;

    for (int i = 1; i <= n; ++i) {
        catalan[i] = 0;
        for (int j = 0; j < i; ++j) {
            catalan[i] += catalan[j] * catalan[i - j - 1];
            catalan[i] %= MOD;  // 모듈러 연산
        }
    }

    cout << catalan[n] << '\n';

    return 0;
}
