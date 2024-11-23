#include <bits/stdc++.h>

#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    int p;
    cin >> n >> p;

    // 특수 케이스 처리: n = 1
    if (n == 1) {
        cout << fixed << setprecision(6) << "0.000000\n";
        return 0;
    }

    // 확률 P = n * (p / 360)^(n-1)
    double log2n = log2((double)n);
    double log2_p_over_360 = log2((double)p / 360.0);
    double log2P = log2n + (n - 1) * log2_p_over_360;

    // -log2 P
    double result = -log2P;

    // 소수점 아래 6자리까지 출력 (반올림)
    cout << fixed << setprecision(6) << result << "\n";
}
