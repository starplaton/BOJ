#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Constants
const int MAX = 200005;

// Tree representation
vector<vector<int>> tree(MAX);
int N, C, Q;

// HLD variables
int parent_node[MAX], depth_node[MAX], heavy[MAX], head[MAX], pos[MAX];
int cur_pos = 0;

// Segment Tree variables
ll c1_tree[4 * MAX], c2_tree[4 * MAX];
ll lazy_c1[4 * MAX], lazy_c2[4 * MAX];

// DFS to compute size and heavy child
int dfs(int v, int p) {
    parent_node[v] = p;
    depth_node[v] = depth_node[p] + 1;
    int size = 1;
    int max_size = 0;
    heavy[v] = -1;
    for (auto &u : tree[v]) {
        if (u != p) {
            int sz = dfs(u, v);
            if (sz > max_size) {
                max_size = sz;
                heavy[v] = u;
            }
            size += sz;
        }
    }
    return size;
}

// Decompose the tree
void decompose(int v, int h) {
    head[v] = h;
    pos[v] = cur_pos++;
    if (heavy[v] != -1) {
        decompose(heavy[v], h);
        for (auto &u : tree[v]) {
            if (u != parent_node[v] && u != heavy[v]) {
                decompose(u, u);
            }
        }
    }
}

// Push down lazy updates
void push(int node, int l, int r) {
    if (lazy_c1[node] != 0 || lazy_c2[node] != 0) {
        c1_tree[node * 2] += lazy_c1[node];
        c2_tree[node * 2] += lazy_c2[node];
        lazy_c1[node * 2] += lazy_c1[node];
        lazy_c2[node * 2] += lazy_c2[node];

        c1_tree[node * 2 + 1] += lazy_c1[node];
        c2_tree[node * 2 + 1] += lazy_c2[node];
        lazy_c1[node * 2 + 1] += lazy_c1[node];
        lazy_c2[node * 2 + 1] += lazy_c2[node];

        lazy_c1[node] = lazy_c2[node] = 0;
    }
}

// Range update in segment tree
void update_range(int node, int l, int r, int L, int R, ll val1, ll val2) {
    if (R < l || L > r) return;
    if (L <= l && r <= R) {
        c1_tree[node] += val1;
        c2_tree[node] += val2;
        lazy_c1[node] += val1;
        lazy_c2[node] += val2;
        return;
    }
    push(node, l, r);
    int mid = (l + r) / 2;
    update_range(node * 2, l, mid, L, R, val1, val2);
    update_range(node * 2 + 1, mid + 1, r, L, R, val1, val2);
}

// Point query in segment tree
pair<ll, ll> query_point(int node, int l, int r, int idx) {
    if (l == r) {
        return {c1_tree[node], c2_tree[node]};
    }
    push(node, l, r);
    int mid = (l + r) / 2;
    if (idx <= mid)
        return query_point(node * 2, l, mid, idx);
    else
        return query_point(node * 2 + 1, mid + 1, r, idx);
}

// Update path from u to v
void update_path(int u, int v) {
    while (head[u] != head[v]) {
        if (depth_node[head[u]] < depth_node[head[v]]) swap(u, v);
        // 수정된 부분: c1=0, c2=1
        update_range(1, 0, N - 1, pos[head[u]], pos[u], 0, 1);
        u = parent_node[head[u]];
    }
    if (depth_node[u] > depth_node[v]) swap(u, v);
    // 수정된 부분: c1=0, c2=1
    update_range(1, 0, N - 1, pos[u], pos[v], 0, 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> C;
    for (int i = 0; i < N - 1; i++) {
        int x, y;
        cin >> x >> y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    // Initialize HLD
    dfs(C, 0);
    decompose(C, C);

    cin >> Q;
    while (Q--) {
        int type, A;
        cin >> type >> A;
        if (type == 1) {
            // Fill operation: update path from root to A
            update_path(C, A);
        } else {
            // Query operation: get water in A
            pair<ll, ll> res = query_point(1, 0, N - 1, pos[A]);
            ll water = res.first + res.second * (ll)depth_node[A];
            cout << water << "\n";
        }
    }
}
