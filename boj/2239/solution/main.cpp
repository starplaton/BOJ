#include <bits/stdc++.h>
using namespace std;

#define all(a) a.begin(), a.end()
#define pii pair<ll, ll>
#define MINI (-0x7fffffff)
#define MAXI (0x3fffffff)
typedef long long ll;

int t, n, m, k;
int chs[9][9];
int v[9][9][10];
int cnt[9][9];

bool isValid(int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (chs[row][i] == num || chs[i][col] == num) {
            return false;
        }
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (chs[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }
    return true;
}

int is_full() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (chs[i][j] == 0) return 0;
        }
    }
    return 1;
}

int dfs() {
    // for (int i = 0; i < 9; i++) {
    //     for (int j = 0; j < 9; j++) {
    //         printf("%d", chs[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (chs[i][j] == 0) {
                for (int k = 1; k <= 9; k++) {
                    if (isValid(i, j, k)) {
                        chs[i][j] = k;
                        if (dfs()) {
                            return 1;
                        }
                        chs[i][j] = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

void solve_2239() {
    for (int i = 0; i < 9; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < 9; j++) {
            chs[i][j] = s[j] - '0';
        }
    }

    dfs();

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d", chs[i][j]);
        }
        printf("\n");
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(false);
    int TC = 1;
    // scanf("%d", &TC);
    while (TC--) solve_2239();
    return 0;
}
