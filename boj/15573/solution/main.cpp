#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

int t, n, m, k;
int ar[1010][1010], v[1010][1010];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
struct xy {
    int y, x;
};

bool poss(int d) {
    memset(v, 0, sizeof v);
    queue<xy> q;
    for (int i = 0; i < n; i++) {
        if (ar[i][0] <= d) {
            q.push({i, 0});
            v[i][0] = 1;
        }
        if (ar[i][m - 1] <= d) {
            q.push({i, m - 1});
            v[i][m - 1] = 1;
        }
    }
    for (int j = 1; j < m - 1; j++) {
        if (ar[0][j] <= d) {
            q.push({0, j});
            v[0][j] = 1;
        }
    }

    while (!q.empty()) {
        xy cur = q.front();
        q.pop();

        for (int dir = 0; dir < 4; dir++) {
            int ny = cur.y + dy[dir];
            int nx = cur.x + dx[dir];
            if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
            if (ar[ny][nx] > d) continue;
            if (v[ny][nx]) continue;
            v[ny][nx] = 1;
            q.push({ny, nx});
        }
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (v[i][j]) cnt++;
        }
    }

    return cnt >= k;
}

void solve_15573() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> ar[i][j];
        }
    }

    int s = 1, e = 1e6;

    int ans = 0;
    while (s <= e) {
        int m = s + e >> 1;

        if (poss(m)) {
            ans = m;
            e = m - 1;
        } else {
            s = m + 1;
        }
    }
    printf("%d\n", ans);
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_15573();
    return 0;
}
