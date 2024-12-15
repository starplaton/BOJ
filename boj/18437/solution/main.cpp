#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Segment Tree with range assignment and range sum
struct SegmentTree {
    int n;
    vector<ll> tree;
    vector<int> lazy;  // -1 means no pending updates, 0 or 1 for pending assignments

    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, -1);
    }

    // Build the tree with initial values
    void build(int node, int l, int r, const vector<int> &initial) {
        if (l == r) {
            tree[node] = initial[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node, l, mid, initial);
        build(2 * node + 1, mid + 1, r, initial);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Push down the lazy updates
    void push(int node, int l, int r) {
        if (lazy[node] != -1) {
            int mid = (l + r) / 2;
            // Update left child
            tree[2 * node] = (mid - l + 1) * (ll)lazy[node];
            lazy[2 * node] = lazy[node];
            // Update right child
            tree[2 * node + 1] = (r - mid) * (ll)lazy[node];
            lazy[2 * node + 1] = lazy[node];
            // Clear the lazy value at current node
            lazy[node] = -1;
        }
    }

    // Range update: set all elements in [ql, qr] to val (0 or 1)
    void update_range(int node, int l, int r, int ql, int qr, int val) {
        if (ql > r || qr < l)
            return;
        if (ql <= l && r <= qr) {
            tree[node] = (r - l + 1) * (ll)val;
            lazy[node] = val;
            return;
        }
        push(node, l, r);
        int mid = (l + r) / 2;
        update_range(2 * node, l, mid, ql, qr, val);
        update_range(2 * node + 1, mid + 1, r, ql, qr, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Range query: sum of elements in [ql, qr]
    ll query_range(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l)
            return 0;
        if (ql <= l && r <= qr)
            return tree[node];
        push(node, l, r);
        int mid = (l + r) / 2;
        return query_range(2 * node, l, mid, ql, qr) + query_range(2 * node + 1, mid + 1, r, ql, qr);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> supervisor(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> supervisor[i];
    }
    // Build tree
    vector<vector<int>> adj(N + 1, vector<int>());
    for (int i = 1; i <= N; ++i) {
        if (supervisor[i] != 0) {
            adj[supervisor[i]].push_back(i);
        }
    }
    // DFS to assign in and out times
    vector<int> in_order(N + 1, 0);
    vector<int> out_order(N + 1, 0);
    int timer = 0;
    // Iterative DFS to avoid stack overflow
    // Using stack of pairs: (node, state)
    // state = 0: first time visiting
    // state = 1: after visiting children
    stack<pair<int, int>> s;
    s.push({1, 0});
    while (!s.empty()) {
        auto [node, state] = s.top();
        s.pop();
        if (state == 0) {
            in_order[node] = ++timer;
            s.push({node, 1});
            // Push children in reverse order to maintain original order
            for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it) {
                s.push({*it, 0});
            }
        } else {
            out_order[node] = timer;
        }
    }
    // Initialize the initial array for Segment Tree
    // We need to map from in_order to employee
    // But since queries are about subtrees, we just need to initialize all to 1
    vector<int> initial(N + 1, 0);  // 1-based
    for (int i = 1; i <= N; ++i) {
        initial[in_order[i]] = 1;
    }
    // Build Segment Tree
    SegmentTree st(N);
    st.build(1, 1, N, initial);
    int M;
    cin >> M;
    while (M--) {
        int type, x;
        cin >> type >> x;
        if (type == 1) {
            // Set to 1 all employees who have x as a superior
            if (in_order[x] + 1 <= out_order[x]) {
                st.update_range(1, 1, N, in_order[x] + 1, out_order[x], 1);
            }
        } else if (type == 2) {
            // Set to 0 all employees who have x as a superior
            if (in_order[x] + 1 <= out_order[x]) {
                st.update_range(1, 1, N, in_order[x] + 1, out_order[x], 0);
            }
        } else if (type == 3) {
            // Query the number of employees who have x as a superior and are on
            if (in_order[x] + 1 <= out_order[x]) {
                ll res = st.query_range(1, 1, N, in_order[x] + 1, out_order[x]);
                cout << res << "\n";
            } else {
                cout << "0\n";
            }
        }
    }
}
