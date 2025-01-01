#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

int t, n, m, k, h;
int ar[202020];
int dp[1'010'101];
string comb[] = {"SRW", "SWR", "WSR", "WRS", "RSW", "RWS"};

void solve_29793() {
    cin >> n >> h;
    string s;
    cin >> s;
    if (h >= 4 && n >= 4) {
        cout << -1;
        return;
    }

    if (h == 1) {
        cout << 0;
        return;
    }

    if (n == 1) {
        cout << 0;
        return;
    }
    if (n == 2) {
        cout << (s[1] == s[0]);
        return;
    }

    if (h == 2) {
        int ans = 0;
        for (int i = 1; i < n; i++) {
            if (s[i] == s[i - 1]) {
                ans++;
                i++;
            }
        }
        cout << ans;
        return;
    }

    if (h >= 3) {
        int ans = 987654321;
        for (int i = 0; i < 6; i++) {
            int local_ans = 0;
            for (int j = 0; j < n; j++) {
                if (s[j] != comb[i][j % 3]) local_ans++;
            }
            ans = min(ans, local_ans);
        }
        cout << ans << "\n";
        return;
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_29793();
    return 0;
}
