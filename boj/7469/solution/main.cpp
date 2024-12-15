#include <bits/stdc++.h>
using namespace std;

struct Node {
    int left;
    int right;
    int cnt;
} nodes[20000000];  // Allocate enough space

int node_cnt = 0;

// Insert val into the tree, return the new root
int insert(int prev, int l, int r, int val) {
    int curr = node_cnt++;
    nodes[curr].cnt = nodes[prev].cnt + 1;

    if (l == r) {
        nodes[curr].left = nodes[curr].right = -1;
        return curr;
    }

    int mid = (l + r) / 2;
    if (val <= mid) {
        nodes[curr].left = insert(nodes[prev].left, l, mid, val);
        nodes[curr].right = nodes[prev].right;
    } else {
        nodes[curr].left = nodes[prev].left;
        nodes[curr].right = insert(nodes[prev].right, mid + 1, r, val);
    }

    return curr;
}

// Find the k-th smallest between two trees
int kth_query(int root_j, int root_i, int l, int r, int k) {
    if (l == r) {
        return l;
    }

    int mid = (l + r) / 2;
    int cnt_left = nodes[nodes[root_j].left].cnt - nodes[nodes[root_i].left].cnt;

    if (k <= cnt_left) {
        return kth_query(nodes[root_j].left, nodes[root_i].left, l, mid, k);
    } else {
        return kth_query(nodes[root_j].right, nodes[root_i].right, mid + 1, r, k - cnt_left);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> a(n);

    for (auto &x : a) {
        cin >> x;
    }

    // Coordinate compression
    vector<int> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());
    sorted_a.erase(unique(sorted_a.begin(), sorted_a.end()), sorted_a.end());

    // Replace a[i] with compressed values
    for (int &x : a) {
        x = lower_bound(sorted_a.begin(), sorted_a.end(), x) - sorted_a.begin() + 1;
    }

    // Initialize root[0]
    vector<int> roots(n + 1);
    nodes[node_cnt].left = nodes[node_cnt].right = -1;
    nodes[node_cnt].cnt = 0;
    roots[0] = node_cnt++;

    // Build persistent segment trees
    for (int i = 1; i <= n; i++) {
        roots[i] = insert(roots[i - 1], 1, n, a[i - 1]);
    }

    // Process queries
    while (m--) {
        int i, j, k;
        cin >> i >> j >> k;
        int res = kth_query(roots[j], roots[i - 1], 1, n, k);

        // Map back to original value
        cout << sorted_a[res - 1] << "\n";
    }

    return 0;
}
