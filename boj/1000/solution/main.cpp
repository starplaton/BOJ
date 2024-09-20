#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

int t, n, m, k;
int ar[202020];

void solve_1000() {
    cin >> n;
    set<int> S;
    for (int i = 0; i < n; i++) cin >> ar[i];
    for (int i = 0; i < n; i++) S.insert(ar[i]);

    if (S.size() & 1)
        cout << "Alice\n";
    else
        cout << "Bob\n";
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    cin >> TC;
    while (TC--) solve_1000();
    return 0;
}
