#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

ll t, n, m, k;

void solve_16282() {
    cin >> n;

    ll b = 8, ans = 1;
    while (n >= b) {
        ans++;
        b = b / ans * (ans + 1) * 2;
    }
    cout << ans;
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_16282();
    return 0;
}
