#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

ll t, n, m, k;
int ar[202020];
string s;
int bit[61];
void solve_16584() {
    cin >> k;
    int blen = 0;
    for (blen = 0; blen <= 60; blen++) {
        bit[blen] = k % 2;
        k >>= 1;
        if (k == 0) {
            break;
        }
    }
    cin >> s;
    // for (int i = 0; i <= blen; i++) {
    //     cout << bit[i];
    // }
    // cout << endl;

    int bidx = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] - '0' == bit[bidx]) {
            bidx++;
        }
    }
    if (blen + 1 == bidx) {
        cout << s.size() - blen - 1;
    } else {
        cout << s.size() - blen;
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_16584();
    return 0;
}
