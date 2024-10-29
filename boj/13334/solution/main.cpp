#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

int n, d;
struct E {
    int s, e;

    bool operator<(const E& other) const {
        // if (e == other.e) return s > other.s;
        return s > other.s;
    }
};
priority_queue<E> pq;

void solve_13334() {
    cin >> n;
    vector<E> v;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        if (x > y) swap(x, y);
        v.push_back({x, y});
    }
    cin >> d;

    sort(all(v), [&](E l, E r) {
        if (l.e == r.e) return l.s < r.s;
        return l.e < r.e;
    });

    int ans = 0;
    for (auto cur : v) {
        int st_e = cur.e;
        if (st_e - cur.s <= d) {
            pq.push(cur);
        }
        while (!pq.empty()) {
            if (st_e - pq.top().s > d) {
                pq.pop();
            } else {
                break;
            }
        }
        ans = max(ans, (int)pq.size());
    }
    cout << ans << endl;
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_13334();
    return 0;
}
