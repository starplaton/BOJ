#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll l, r;
    cin >> l >> r;

    ll count = 0;
    // p는 0부터 200까지 반복 (안전하게 p_max=148 포함)
    for (ll p = 0; p <= 200; p++) {
        ll p6 = 1;
        bool overflow = false;
        for (int i = 0; i < 6; i++) {
            if (p > 1e18) {
                overflow = true;
                break;
            }
            p6 *= p;
            if (p6 > 1e18) {
                overflow = true;
                break;
            }
        }
        if (overflow) {
            continue;
        }
        ll x = 36000 * p6;
        // x가 0일 때 l <=0 <=r인지 확인
        if (x < l) {
            continue;
        }
        if (x > r) {
            continue;
        }
        count++;
    }
    cout << count;
    return 0;
}
