#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// BIT (Fenwick Tree) for range updates and point queries
struct BIT {
    int n;
    vector<ll> tree;

    BIT(int size) : n(size), tree(size + 1, 0) {}

    void add(int idx, ll val) {
        while (idx <= n) {
            tree[idx] += val;
            idx += idx & -idx;
        }
    }

    void range_add(int l, int r, ll val) {
        add(l, val);
        add(r + 1, -val);
    }

    ll query(int idx) const {
        ll res = 0;
        int i = idx;
        while (i > 0) {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // parent[1] = -1
    vector<int> parent(n + 1, -1);
    for (int i = 1; i <= n; ++i) {
        cin >> parent[i];
    }

    // Build the tree
    vector<vector<int>> adj(n + 1, vector<int>());
    int root = -1;
    for (int i = 1; i <= n; ++i) {
        if (parent[i] == -1) {
            root = i;
        } else {
            adj[parent[i]].push_back(i);
        }
    }

    // Initialize HLD variables
    vector<int> size_subtree(n + 1, 0);
    vector<int> depth_v(n + 1, 0);
    vector<int> heavy(n + 1, -1);
    vector<int> head(n + 1, -1);
    vector<int> pos(n + 1, 0);
    int current_pos = 1;

    // First DFS to compute size and heavy child
    function<void(int)> dfs1 = [&](int v) {
        size_subtree[v] = 1;
        int max_size = 0;
        for (auto &child : adj[v]) {
            depth_v[child] = depth_v[v] + 1;
            dfs1(child);
            size_subtree[v] += size_subtree[child];
            if (size_subtree[child] > max_size) {
                max_size = size_subtree[child];
                heavy[v] = child;
            }
        }
    };

    // Second DFS to assign head and positions
    function<void(int, int)> dfs2 = [&](int v, int h) {
        head[v] = h;
        pos[v] = current_pos++;
        if (heavy[v] != -1) {
            dfs2(heavy[v], h);
            for (auto &child : adj[v]) {
                if (child != heavy[v]) {
                    dfs2(child, child);
                }
            }
        } else {
            // Leaf node
            return;
        }
    };

    dfs1(root);
    dfs2(root, root);

    // Initialize BIT
    BIT bit(n);

    // Process queries
    for (int i = 0; i < m; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int u;
            ll w;
            cin >> u >> w;
            // Update the path from u to root
            int v = root;
            while (head[u] != head[v]) {
                bit.range_add(pos[head[u]], pos[u], w);
                u = parent[head[u]];
            }
            if (depth_v[u] < depth_v[v]) {
                swap(u, v);
            }
            bit.range_add(pos[v], pos[u], w);
        } else if (type == 2) {
            int u;
            cin >> u;
            cout << bit.query(pos[u]) << "\n";
        }
    }
}
