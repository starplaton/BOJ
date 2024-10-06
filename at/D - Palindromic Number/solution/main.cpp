#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

int o[1010];
int length = 0;

void solve_1000() {
    ll n;
    cin >> n;

    if (n == 1) {
        cout << 0;
        return;
    }
    ll cnt = 0;
    n--;
    n--;
    for (int i = 0; i <= 18; i++) {
        length++;
        cnt += 9LL * (ll)pow(10, i);
        if (n < cnt) {
            // ll a = cnt - 9LL * pow(10, i);
            n -= cnt - 9LL * (ll)pow(10, i);
            break;
        }
        length++;
        cnt += 9LL * (ll)pow(10, i);
        if (n < cnt) {
            n -= cnt - 9LL * (ll)pow(10, i);
            break;
        }
    }

    int idx = 0;
    int total_length = length;
    length = (length + 1) / 2 - 1;
    n += 1LL * (ll)pow(10, length);
    while (length >= idx) {
        if (total_length % 2 == 1) {
            o[length - idx] = o[length + idx] = n % 10;
        } else {
            o[length - idx] = o[length + 1 + idx] = n % 10;
        }
        idx++;
        n /= 10;
    }

    for (int i = 0; i < total_length; i++) {
        cout << o[i];
    }
    cout << '\n';
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // cin >> TC;
    while (TC--) solve_1000();
    return 0;
}