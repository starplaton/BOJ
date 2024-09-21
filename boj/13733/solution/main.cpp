#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

struct coord {
    int x, y;
};
int t, n, m, k;
coord A[3], B[3];

coord merge(int x1, int y1, int x2, int y2) {
    if (y1 == y2) {
        return {y1, x1 + x2};
    }
    if (y1 == x2) {
        return {y1, x1 + y2};
    }
    if (x1 == x2) {
        return {x1, y1 + y2};
    }
    if (x1 == y2) {
        return {x1, y1 + x2};
    }
    return {-1, -1};
}
void solve_13733() {
    for (int i = 0; i < 3; i++) {
        int a, b;
        cin >> a >> b;
        A[i] = {a, b};
    }

    int p[3] = {0, 1, 2};
    string ans = "NO";
    do {
        for (int i = 0; i < 3; i++) B[i] = A[p[i]];
        coord M = merge(B[0].x, B[0].y, B[1].x, B[1].y);
        M = merge(M.x, M.y, B[2].x, B[2].y);
        if (M.x == -1) continue;
        if (M.x == M.y) ans = "YES";
    } while (next_permutation(p, p + 3));

    do {
        for (int i = 0; i < 3; i++) B[i] = {A[p[i]].y, A[p[i]].x};
        coord M = merge(B[0].x, B[0].y, B[1].x, B[1].y);
        M = merge(M.x, M.y, B[2].x, B[2].y);
        if (M.x == -1) continue;
        if (M.x == M.y) ans = "YES";
    } while (next_permutation(p, p + 3));
    cout << ans << '\n';
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_13733();
    return 0;
}
