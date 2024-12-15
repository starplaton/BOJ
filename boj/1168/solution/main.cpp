#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Struct for Binary Indexed Tree (Fenwick Tree)
struct BIT {
    int n;
    vector<int> tree;

    BIT(int size) : n(size), tree(size + 1, 0) {
        for (int i = 1; i <= n; i++) {
            add(i, 1);
        }
    }

    void add(int idx, int delta) {
        while (idx <= n) {
            tree[idx] += delta;
            idx += idx & -idx;
        }
    }

    // Returns the sum of the first idx elements
    int sum(int idx) const {
        int res = 0;
        int t = idx;
        // Since sum is not modified, we need to cast tree to non-const
        // So we make the sum function non-const
        // To avoid this, we can make tree mutable or make sum non-const
        // Here, we use a workaround
        BIT* self = const_cast<BIT*>(this);
        while (t > 0) {
            res += self->tree[t];
            t -= t & -t;
        }
        return res;
    }

    // Finds the position of the k-th one
    int find_kth(int k) const {
        int idx = 0;
        int bitMask = 1;
        while (bitMask <= n) bitMask <<= 1;
        bitMask >>= 1;
        while (bitMask > 0) {
            int t = idx + bitMask;
            if (t <= n) {
                BIT* self = const_cast<BIT*>(this);
                if (self->tree[t] < k) {
                    idx = t;
                    k -= self->tree[t];
                }
            }
            bitMask >>= 1;
        }
        return idx + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, K;
    cin >> N >> K;
    BIT bit(N);
    vector<int> result;
    int current_index = 0;
    for (int i = 0; i < N; i++) {
        int rem = N - i;
        current_index = (current_index + K - 1) % rem;
        int kth = current_index + 1;
        int idx = bit.find_kth(kth);
        result.push_back(idx);
        bit.add(idx, -1);
    }
    // Print in the required format
    cout << "<";
    for (int i = 0; i < result.size(); i++) {
        if (i > 0) cout << ", ";
        cout << result[i];
    }
    cout << ">";
}
