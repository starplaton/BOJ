#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;

vector<int> tree[MAXN];
int parent[MAXN], heavy[MAXN], depth[MAXN], head[MAXN], pos[MAXN], sz[MAXN];
int cur_pos;
int N, Q;

uint32_t sum[MAXN * 4];
uint32_t lazy_mul[MAXN * 4];
uint32_t lazy_add[MAXN * 4];

void dfs_size(int u, int p) {
    sz[u] = 1;
    parent[u] = p;
    depth[u] = depth[p] + 1;
    int max_size = 0;
    heavy[u] = -1;
    for (int v : tree[u]) {
        if (v != p) {
            dfs_size(v, u);
            sz[u] += sz[v];
            if (sz[v] > max_size) {
                max_size = sz[v];
                heavy[u] = v;
            }
        }
    }
}

void dfs_hld(int u, int h) {
    head[u] = h;
    pos[u] = cur_pos++;
    if (heavy[u] != -1) {
        dfs_hld(heavy[u], h);
        for (int v : tree[u]) {
            if (v != parent[u] && v != heavy[u]) {
                dfs_hld(v, v);
            }
        }
    }
}

void build(int node, int l, int r) {
    lazy_mul[node] = 1;
    lazy_add[node] = 0;
    sum[node] = 0;
    if (l == r) {
        // sum[node] = initial value at position l
        return;
    }
    int m = (l + r) / 2;
    build(node * 2, l, m);
    build(node * 2 + 1, m + 1, r);
}

void push(int node, int l, int r) {
    if (lazy_mul[node] != 1 || lazy_add[node] != 0) {
        sum[node] = (uint32_t)((uint64_t)sum[node] * lazy_mul[node] + (uint64_t)lazy_add[node] * (r - l + 1));

        if (l != r) {
            int lc = node * 2;
            int rc = node * 2 + 1;

            lazy_mul[lc] = (uint32_t)((uint64_t)lazy_mul[lc] * lazy_mul[node]);
            lazy_add[lc] = (uint32_t)((uint64_t)lazy_add[lc] * lazy_mul[node] + lazy_add[node]);

            lazy_mul[rc] = (uint32_t)((uint64_t)lazy_mul[rc] * lazy_mul[node]);
            lazy_add[rc] = (uint32_t)((uint64_t)lazy_add[rc] * lazy_mul[node] + lazy_add[node]);
        }

        lazy_mul[node] = 1;
        lazy_add[node] = 0;
    }
}

void update_range(int node, int l, int r, int ql, int qr, uint32_t mul, uint32_t add) {
    push(node, l, r);
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
        lazy_mul[node] = (uint32_t)((uint64_t)lazy_mul[node] * mul);
        lazy_add[node] = (uint32_t)((uint64_t)lazy_add[node] * mul + add);
        push(node, l, r);
        return;
    }
    int m = (l + r) / 2;
    update_range(node * 2, l, m, ql, qr, mul, add);
    update_range(node * 2 + 1, m + 1, r, ql, qr, mul, add);
    sum[node] = sum[node * 2] + sum[node * 2 + 1];
}

uint32_t query_range(int node, int l, int r, int ql, int qr) {
    push(node, l, r);
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) {
        return sum[node];
    }
    int m = (l + r) / 2;
    return query_range(node * 2, l, m, ql, qr) + query_range(node * 2 + 1, m + 1, r, ql, qr);
}

void path_update(int u, int v, uint32_t mul, uint32_t add) {
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        int start = pos[head[u]];
        int end = pos[u];
        update_range(1, 0, N - 1, start, end, mul, add);
        u = parent[head[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    update_range(1, 0, N - 1, pos[u], pos[v], mul, add);
}

uint32_t path_query(int u, int v) {
    uint32_t res = 0;
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        int start = pos[head[u]];
        int end = pos[u];
        res += query_range(1, 0, N - 1, start, end);
        u = parent[head[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    res += query_range(1, 0, N - 1, pos[u], pos[v]);
    return res;
}

void subtree_update(int u, uint32_t mul, uint32_t add) {
    update_range(1, 0, N - 1, pos[u], pos[u] + sz[u] - 1, mul, add);
}

uint32_t subtree_query(int u) {
    return query_range(1, 0, N - 1, pos[u], pos[u] + sz[u] - 1);
}

int main() {
    scanf("%d %d", &N, &Q);
    for (int i = 1; i <= N - 1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    depth[0] = -1;
    dfs_size(1, 0);
    cur_pos = 0;
    dfs_hld(1, 1);

    build(1, 0, N - 1);

    for (int i = 0; i < Q; ++i) {
        int cmd;
        scanf("%d", &cmd);
        if (cmd == 1) {
            int X;
            uint32_t V;
            scanf("%d %u", &X, &V);
            subtree_update(X, 1, V);
        } else if (cmd == 2) {
            int X, Y;
            uint32_t V;
            scanf("%d %d %u", &X, &Y, &V);
            path_update(X, Y, 1, V);
        } else if (cmd == 3) {
            int X;
            uint32_t V;
            scanf("%d %u", &X, &V);
            subtree_update(X, V, 0);
        } else if (cmd == 4) {
            int X, Y;
            uint32_t V;
            scanf("%d %d %u", &X, &Y, &V);
            path_update(X, Y, V, 0);
        } else if (cmd == 5) {
            int X;
            scanf("%d", &X);
            uint32_t ans = subtree_query(X);
            printf("%u\n", ans);
        } else if (cmd == 6) {
            int X, Y;
            scanf("%d %d", &X, &Y);
            uint32_t ans = path_query(X, Y);
            printf("%u\n", ans);
        }
    }

    return 0;
}
