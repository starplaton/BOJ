#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

int t, n, m, k;
int ar[202020];

void solve_6198() {
    cin >> n;
    int st[80808] = {0};
    int idx = 0;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        while (idx > 0 && st[idx - 1] <= x) {
            idx--;
        }
        ans += max(0, idx);
        // cout << ans << '\n';
        st[idx++] = x;
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_6198();
    return 0;
}
