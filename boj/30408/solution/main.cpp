#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

ll t, n, m, k;
int ar[202020];

void solve_30408() {
    cin >> n >> m;

    ll curs = m;
    ll cure = m;

    while (curs <= n) {
        if (curs <= n && n <= cure) {
            cout << "YES\n";
            return;
        }
        curs = curs * 2 - 1;
        cure = cure * 2 + 1;
    }

    cout << "NO\n";
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_30408();
    return 0;
}
