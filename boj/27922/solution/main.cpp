#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

int t, n, m, k;
int ar[202020], br[202020], cr[202020];
vector<int> v[3];

void solve_27922() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> ar[i] >> br[i] >> cr[i];
    }
    for (int i = 0; i < n; i++) {
        v[0].push_back(ar[i] + br[i]);
        v[1].push_back(br[i] + cr[i]);
        v[2].push_back(cr[i] + ar[i]);
    }

    sort(all(v[0]));
    sort(all(v[1]));
    sort(all(v[2]));

    int ans[3] = {0};
    for (int i = 0; i < k; i++) {
        ans[0] += v[0][n - 1 - i];
        ans[1] += v[1][n - 1 - i];
        ans[2] += v[2][n - 1 - i];
    }

    cout << max({ans[0], ans[1], ans[2]});
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_27922();
    return 0;
}
