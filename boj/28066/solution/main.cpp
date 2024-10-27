#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

int t, n, m, k;
int ar[1010101];

void solve_28066() {
    cin >> n >> k;
    queue<int> q;
    for (int i = 1; i <= n; i++) q.push(i);

    while (q.size() != 1) {
        int cur = q.front();
        q.pop();
        int cnt = k - 1;
        while (!q.empty() && cnt--) {
            q.pop();
        }
        q.push(cur);
    }
    cout << q.front() << '\n';
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_28066();
    return 0;
}
