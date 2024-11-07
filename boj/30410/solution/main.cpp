#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 3, K = 60;
int n, L[K][N], R[K][N], maxDepth;

int main() {
    cin >> n;
    fill(&L[0][0], &L[K - 1][N], n + 1);

    for (int i = 1; i <= n; ++i) {
        int a;
        cin >> a;
        L[a][i] = R[a][i] = i;
        maxDepth = max(maxDepth, a);
    }

    for (int i = 1; i <= 58; ++i) {
        for (int j = 1; j < n; ++j) {
            int left = L[i][j], right = R[i][j + 1];
            if (left > j || right < j + 1) continue;
            L[i + 1][right] = left;
            R[i + 1][left] = right;
            maxDepth = max(maxDepth, i + 1);
        }
    }

    cout << (1LL << (maxDepth - 1)) << '\n';
    return 0;
}
