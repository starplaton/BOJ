#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

int t, n, m, k;
int ar[202020];
int ans[202020];

void solve_2304() {
    cin >> n;
    int maxh = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        ar[a] = b;
        maxh = max(maxh, b);
    }

    int lmax = 0;
    int st, ed;
    for (st = 0; st <= 1000; st++) {
        if (ar[st] == maxh) break;
        lmax = max(lmax, ar[st]);
        ans[st] = lmax;
    }
    lmax = 0;
    for (ed = 1000; ed >= 0; ed--) {
        if (ar[ed] == maxh) break;
        lmax = max(lmax, ar[ed]);
        ans[ed] = lmax;
    }
    int sum = 0;
    for (int i = st; i <= ed; i++) {
        sum += maxh;
    }

    for (int i = 0; i <= 1000; i++) {
        sum += ans[i];
        // cout << ans[i] << " ";
    }
    // cout << "\n";
    cout << sum << '\n';
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_2304();
    return 0;
}
