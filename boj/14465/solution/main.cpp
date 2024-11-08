#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

int t, n, k, b;
int ar[202020], pr[202020];

void solve_14465() {
    cin >> n >> k >> b;
    for (int i = 0; i < b; i++) {
        int x;
        cin >> x;
        ar[x] = 1;
    }

    for (int i = 1; i <= n; i++) pr[i] = pr[i - 1] + ar[i];

    int ans = 202020;
    for (int i = k; i <= n; i++) {
        ans = min(ans, pr[i] - pr[i - k]);
    }
    cout << ans;
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_14465();
    return 0;
}
