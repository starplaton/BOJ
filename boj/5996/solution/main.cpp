#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

int T, C, Ts, Te;
int ar[202020];
struct E {
    int t, c;
};
vector<E> g[2525];
int q[9'101'010];

void solve_5996() {
    cin >> T >> C >> Ts >> Te;
    for (int i = 0; i < C; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }

    int cst[2525] = {0};
    for (int i = 0; i < 2525; i++) cst[i] = 987654321;
    cst[Ts] = 0;

    int qs = 0, qe = 0;
    q[qe++] = Ts;
    while (qs < qe) {
        int cur = q[qs++];
        for (auto tgt : g[cur]) {
            if (cst[cur] + tgt.c > cst[tgt.t]) continue;
            cst[tgt.t] = cst[cur] + tgt.c;
            q[qe++] = tgt.t;
        }
    }
    for (int i = 1; i <= T; i++) {
        printf("%d ", cst[i]);
    }
    printf("\n");

    cout << cst[Te] << '\n';
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_5996();
    return 0;
}
