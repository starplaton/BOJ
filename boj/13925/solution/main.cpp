#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX = 100005;
const ll MOD = 1000000007;

// 세그먼트 트리 노드 구조체
struct Node {
    ll sum;        // 구간 합
    ll add_lazy;   // 지연된 덧셈 값
    ll mul_lazy;   // 지연된 곱셈 값
    ll set_lazy;   // 지연된 대입 값
    bool has_set;  // 대입 연산 여부

    Node() : sum(0), add_lazy(0), mul_lazy(1), set_lazy(0), has_set(false) {}
} tree_node[MAX * 4];

// 원본 배열
ll A[MAX];

// 세그먼트 트리 빌드
void build(int node, int l, int r) {
    if (l == r) {
        tree_node[node].sum = A[l] % MOD;
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    tree_node[node].sum = (tree_node[node * 2].sum + tree_node[node * 2 + 1].sum) % MOD;
}

// 푸시다운: 현재 노드의 지연된 연산을 자식 노드로 전달
void push_down(int node, int l, int r) {
    if (tree_node[node].has_set) {
        // 대입 연산은 기존의 덧셈, 곱셈 연산을 덮어씀
        ll val = tree_node[node].set_lazy;
        int mid = (l + r) / 2;
        // 왼쪽 자식
        tree_node[node * 2].sum = (val * (mid - l + 1)) % MOD;
        tree_node[node * 2].set_lazy = val;
        tree_node[node * 2].mul_lazy = 1;
        tree_node[node * 2].add_lazy = 0;
        tree_node[node * 2].has_set = true;
        // 오른쪽 자식
        tree_node[node * 2 + 1].sum = (val * (r - mid)) % MOD;
        tree_node[node * 2 + 1].set_lazy = val;
        tree_node[node * 2 + 1].mul_lazy = 1;
        tree_node[node * 2 + 1].add_lazy = 0;
        tree_node[node * 2 + 1].has_set = true;
        // 현재 노드의 지연 연산 초기화
        tree_node[node].has_set = false;
    }

    // 곱셈 연산 푸시다운
    if (tree_node[node].mul_lazy != 1) {
        ll mul = tree_node[node].mul_lazy;
        int mid = (l + r) / 2;
        // 왼쪽 자식
        tree_node[node * 2].sum = (tree_node[node * 2].sum * mul) % MOD;
        if (tree_node[node * 2].has_set) {
            tree_node[node * 2].set_lazy = (tree_node[node * 2].set_lazy * mul) % MOD;
        } else {
            tree_node[node * 2].mul_lazy = (tree_node[node * 2].mul_lazy * mul) % MOD;
            tree_node[node * 2].add_lazy = (tree_node[node * 2].add_lazy * mul) % MOD;
        }
        // 오른쪽 자식
        tree_node[node * 2 + 1].sum = (tree_node[node * 2 + 1].sum * mul) % MOD;
        if (tree_node[node * 2 + 1].has_set) {
            tree_node[node * 2 + 1].set_lazy = (tree_node[node * 2 + 1].set_lazy * mul) % MOD;
        } else {
            tree_node[node * 2 + 1].mul_lazy = (tree_node[node * 2 + 1].mul_lazy * mul) % MOD;
            tree_node[node * 2 + 1].add_lazy = (tree_node[node * 2 + 1].add_lazy * mul) % MOD;
        }
        // 현재 노드의 곱셈 지연값 초기화
        tree_node[node].mul_lazy = 1;
    }

    // 덧셈 연산 푸시다운
    if (tree_node[node].add_lazy != 0) {
        ll add = tree_node[node].add_lazy;
        int mid = (l + r) / 2;
        // 왼쪽 자식
        tree_node[node * 2].sum = (tree_node[node * 2].sum + add * (mid - l + 1)) % MOD;
        if (tree_node[node * 2].has_set) {
            tree_node[node * 2].set_lazy = (tree_node[node * 2].set_lazy + add) % MOD;
        } else {
            tree_node[node * 2].add_lazy = (tree_node[node * 2].add_lazy + add) % MOD;
        }
        // 오른쪽 자식
        tree_node[node * 2 + 1].sum = (tree_node[node * 2 + 1].sum + add * (r - mid)) % MOD;
        if (tree_node[node * 2 + 1].has_set) {
            tree_node[node * 2 + 1].set_lazy = (tree_node[node * 2 + 1].set_lazy + add) % MOD;
        } else {
            tree_node[node * 2 + 1].add_lazy = (tree_node[node * 2 + 1].add_lazy + add) % MOD;
        }
        // 현재 노드의 덧셈 지연값 초기화
        tree_node[node].add_lazy = 0;
    }
}

// 업데이트: l ~ r 구간에 연산을 적용
// type: 1 - add, 2 - multiply, 3 - set
// val: 연산에 사용할 값
void update(int node, int l, int r, int ul, int ur, int type, ll val) {
    if (ul > r || ur < l)
        return;
    if (ul <= l && r <= ur) {
        if (type == 1) {
            // 덧셈
            tree_node[node].sum = (tree_node[node].sum + val * (r - l + 1)) % MOD;
            if (tree_node[node].has_set) {
                tree_node[node].set_lazy = (tree_node[node].set_lazy + val) % MOD;
            } else {
                tree_node[node].add_lazy = (tree_node[node].add_lazy + val) % MOD;
            }
        } else if (type == 2) {
            // 곱셈
            tree_node[node].sum = (tree_node[node].sum * val) % MOD;
            if (tree_node[node].has_set) {
                tree_node[node].set_lazy = (tree_node[node].set_lazy * val) % MOD;
            } else {
                tree_node[node].mul_lazy = (tree_node[node].mul_lazy * val) % MOD;
                tree_node[node].add_lazy = (tree_node[node].add_lazy * val) % MOD;
            }
        } else if (type == 3) {
            // 대입
            tree_node[node].sum = (val * (r - l + 1)) % MOD;
            tree_node[node].set_lazy = val;
            tree_node[node].mul_lazy = 1;
            tree_node[node].add_lazy = 0;
            tree_node[node].has_set = true;
        }
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    update(node * 2, l, mid, ul, ur, type, val);
    update(node * 2 + 1, mid + 1, r, ul, ur, type, val);
    tree_node[node].sum = (tree_node[node * 2].sum + tree_node[node * 2 + 1].sum) % MOD;
}

// 쿼리: l ~ r 구간의 합을 구함
ll query_sum(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l)
        return 0;
    if (ql <= l && r <= qr) {
        return tree_node[node].sum;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    return (query_sum(node * 2, l, mid, ql, qr) + query_sum(node * 2 + 1, mid + 1, r, ql, qr)) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> A[i];

    build(1, 1, N);

    int M;
    cin >> M;
    while (M--) {
        int type;
        cin >> type;
        if (type == 1 || type == 2 || type == 3) {
            int x, y;
            ll v;
            cin >> x >> y;
            if (type != 4) cin >> v;
            if (type == 1 || type == 2) {
                update(1, 1, N, x, y, type, v);
            } else if (type == 3) {
                update(1, 1, N, x, y, type, v % MOD);
            }
        } else if (type == 4) {
            int x, y;
            cin >> x >> y;
            ll res = query_sum(1, 1, N, x, y);
            cout << res % MOD << '\n';
        }
    }
}
