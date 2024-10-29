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
int bit[64];
void solve_16584() {
    cin >> k;
    int blen = 0;
    for (blen = 1; blen <= 64; blen++) {
        bit[blen] = k % 2;
        k >>= 1;
        if (k == 0) {
            break;
        }
    }
    cin >> s;
    // for (int i = 1; i <= blen; i++) {
    //     cout << bit[i];
    // }
    // cout << endl;

    int bidx = 1;
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] - '0' == bit[bidx]) {
            bidx++;
        } else if (s[i] - '0' == 0) {
            bidx++;
        }
        if (bidx >= blen) break;
    }
    if (blen == bidx) {
        cout << s.size() - blen;
    } else {
        cout << s.size() - blen + 1;
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_16584();
    return 0;
}
