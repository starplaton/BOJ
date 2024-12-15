#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Node {
    Node *l, *r;
    ll v;
    Node() {
        l = r = NULL;
        v = 0;
    }
};

Node *root[102020];
int ar[102020];

void build(Node *node, int s, int e) {
    if (s == e) {
        node->v = ar[s];
        return;
    }
    int m = s + e >> 1;
    node->l = new Node();
    node->r = new Node();
    build(node->l, s, m);
    build(node->r, m + 1, e);
    node->v = node->l->v + node->r->v;
}

void add(Node *prv, Node *now, int s, int e, int x, int v) {
    if (s == e) {
        now->v = v;
        return;
    }
    int m = s + e >> 1;
    if (x <= m) {
        now->l = new Node();
        now->r = prv->r;
        add(prv->l, now->l, s, m, x, v);
    } else {
        now->r = new Node();
        now->l = prv->l;
        add(prv->r, now->r, m + 1, e, x, v);
    }
    now->v = now->l->v + now->r->v;
}

ll query(Node *node, int s, int e, int l, int r) {
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return node->v;
    int m = s + e >> 1;
    return query(node->l, s, m, l, r) + query(node->r, m + 1, e, l, r);
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) scanf("%d", &ar[i]);

    int m;
    scanf("%d", &m);
    int idx = 0;
    build(root[idx++], 1, n);

    for (int q = 0; q < m; q++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int i, v;
            scanf("%d %d", &i, &v);
            add(root[idx - 1], root[idx], 1, n, i, v);
            idx++;
        } else if (op == 2) {
            int k, i, j;
            scanf("%d %d %d", &k, &i, &j);
            printf("%lld\n", query(root[k], 1, n, i, j));
        }
    }
}