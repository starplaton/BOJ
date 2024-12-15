#include <bits/stdc++.h>
using namespace std;

struct Event {
    int x;
    int type;  // 1 for entering, -1 for leaving
    int y1, y2;
    bool operator<(const Event& other) const {
        if (x != other.x)
            return x < other.x;
        return type > other.type;  // Entering events before leaving
    }
};

struct SegmentTree {
    int left, right;
    int count;
    long long total;
} treeNode;

class SegTree {
   public:
    int n;
    vector<SegmentTree> tree;
    vector<int> y;

    SegTree(int size, const vector<int>& y_coords) {
        n = size - 1;
        y = y_coords;
        tree.resize(4 * n, SegmentTree{0, 0, 0, 0});
        build(1, 0, n);
    }

    void build(int node, int l, int r) {
        tree[node].left = l;
        tree[node].right = r;
        tree[node].count = 0;
        tree[node].total = 0;
        if (r - l <= 1)
            return;
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid, r);
    }

    void update(int node, int l, int r, int val) {
        if (tree[node].right <= l || tree[node].left >= r)
            return;
        if (tree[node].left >= l && tree[node].right <= r) {
            tree[node].count += val;
            pushup(node);
            return;
        }
        update(node * 2, l, r, val);
        update(node * 2 + 1, l, r, val);
        pushup(node);
    }

    void pushup(int node) {
        if (tree[node].count > 0) {
            tree[node].total = y[tree[node].right] - y[tree[node].left];
        } else {
            if (tree[node].right - tree[node].left <= 1) {
                tree[node].total = 0;
            } else {
                tree[node].total = tree[node * 2].total + tree[node * 2 + 1].total;
            }
        }
    }

    long long query() const {
        return tree[1].total;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<Event> events;
    vector<int> ys;
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        events.push_back(Event{x1, 1, y1, y2});
        events.push_back(Event{x2, -1, y1, y2});
        ys.push_back(y1);
        ys.push_back(y2);
    }
    // Coordinate compression
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    // Replace y coordinates with compressed indices
    for (auto& e : events) {
        e.y1 = lower_bound(ys.begin(), ys.end(), e.y1) - ys.begin();
        e.y2 = lower_bound(ys.begin(), ys.end(), e.y2) - ys.begin();
    }
    // Sort events
    sort(events.begin(), events.end());
    // Initialize segment tree
    SegTree st(ys.size(), ys);
    long long total_area = 0;
    int last_x = events[0].x;
    st.update(1, events[0].y1, events[0].y2, events[0].type);
    for (int i = 1; i < events.size(); i++) {
        int current_x = events[i].x;
        long long covered_y = st.query();
        total_area += (long long)(current_x - last_x) * covered_y;
        st.update(1, events[i].y1, events[i].y2, events[i].type);
        last_x = current_x;
    }
    cout << total_area;
}
