#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

ll t, n, a, b;
ll bit[31], miv[31], mav[31];
ll dp[31][10101];

int get_dp(int x, int mo) {
    if (x == -1) {
        if (mo == 0) return 1;
        return 0;
    }
    if (dp[x][mo] != -1) return dp[x][mo];
    ll sum = get_dp(x - 1, (mo + (1 << x)) % a);
    if (!bit[x]) sum += get_dp(x - 1, mo);

    return dp[x][mo] = sum;
}

int get_count(int x, int to) {
    if (to + miv[x] > b) return 0;
    if (to + mav[x] <= b) return get_dp(x, to % a);

    ll sum = get_count(x - 1, to + (1 << x));
    if (!bit[x]) sum += get_count(x - 1, to);
    return sum;
}

void solve_16153() {
    memset(dp, -1, sizeof dp);
    cin >> n >> a >> b;
    int bitset = 0, cnt = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        bit[x] = 1;
        bitset |= (1 << x);
    }

    if (a >= 10000) {
        for (ll i = a; i <= b; i += a) {
            if ((i & bitset) == bitset) cnt++;
        }
        printf("%d\n", cnt);
        return;
    }

    for (int i = 0; i < 31; i++) {
        miv[i] = (1 << i) * bit[i];
        if (i) miv[i] += miv[i - 1];

        mav[i] = 1 << i;
        if (i) mav[i] += mav[i - 1];
    }

    cnt = get_count(30, 0);
    if (n == 0) cnt--;

    printf("%d\n", cnt);
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_16153();
    return 0;
}
