#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;

    vector<int> R(N);
    for (int i = 0; i < N; ++i) {
        cin >> R[i];
    }

    vector<int> C(N);
    for (int i = 0; i < N; ++i) {
        cin >> C[i];
    }

    // Assign connected components for rows
    vector<int> row_component(N + 1, 0);
    row_component[1] = 1;
    int current_row_component = 1;
    for (int i = 2; i <= N; ++i) {
        if ((R[i - 2] % 2) == (R[i - 1] % 2)) {
            row_component[i] = current_row_component;
        } else {
            current_row_component++;
            row_component[i] = current_row_component;
        }
    }

    // Assign connected components for columns
    vector<int> column_component(N + 1, 0);
    column_component[1] = 1;
    int current_column_component = 1;
    for (int j = 2; j <= N; ++j) {
        if ((C[j - 2] % 2) == (C[j - 1] % 2)) {
            column_component[j] = current_column_component;
        } else {
            current_column_component++;
            column_component[j] = current_column_component;
        }
    }

    // Prepare output
    string output;
    output.reserve(Q * 4);  // "YES\n" or "NO\n", reserve enough space

    for (int q = 0; q < Q; ++q) {
        int ra, ca, rb, cb;
        cin >> ra >> ca >> rb >> cb;
        if (row_component[ra] == row_component[rb] && column_component[ca] == column_component[cb]) {
            output += "YES\n";
        } else {
            output += "NO\n";
        }
    }

    cout << output;

    return 0;
}
