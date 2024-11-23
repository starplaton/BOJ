#include <string.h>

#include <iostream>
#include <vector>
using namespace std;

vector<int> adj[200001];
int depth[200001];
int first[200001], last[200001], I;
int fenwick[400003];

// monkey is mononknkey
void mon(int root) {
    first[root] = I++;
    for (int child : adj[root])
        if (first[child] == -1) {
            depth[child] = depth[root] + 1;
            mon(child);
        }
    last[root] = I++;
}

void onk(int idx, int del) {
    idx++;
    while (idx <= I) {
        fenwick[idx] += del;
        idx += (idx & -idx);
    }
}

int nkey(int idx) {
    int ret = 0;
    idx++;
    while (idx > 0) {
        ret += fenwick[idx];
        idx &= idx - 1;
    }
    return ret;
}

int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    int N, C, Q;
    cin >> N >> C;
    for (int i = 0; i < N - 1; i++) {
        int A, B;
        cin >> A >> B;
        adj[A].push_back(B);
        adj[B].push_back(A);
    }

    memset(first, -1, sizeof(first));
    depth[C] = 1;
    mon(C);

    cin >> Q;
    while (Q--) {
        int T, A;
        cin >> T >> A;
        if (T == 1)
            onk(first[A], 1);
        else
            cout << (long long)(nkey(last[A]) - nkey(first[A] - 1)) * depth[A] << '\n';
    }
}