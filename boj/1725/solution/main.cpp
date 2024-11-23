#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

int t, n, m, k;
int ar[202020];

void solve_1725() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> ar[i];
    ar[n] = 0;
    int ans = 0;

    stack<int> st;
    st.push(ar[0]);
    for (int i = 1; i <= n; i++) {
        if (ar[i] >= st.top()) {
            st.push(ar[i]);
        } else {
            int len = 1;
            while (!st.empty() && ar[i] < st.top()) {
                int cur = st.top();
                st.pop();
                ans = max(ans, len * cur);
                len++;
            }
            for (int k = 0; k < len - 1; k++) st.push(ar[i]);
            st.push(ar[i]);
        }
        // printf("stack size:%d\n", st.size());
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_1725();
    return 0;
}
