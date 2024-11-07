#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> answers(m);
    for (auto &x : answers) cin >> x;
    cout << 2 * m + 1 << "\n";
    cout << "U 1 -10000\n";
    for (int i = 0; i < m; i++) {
        int d = answers[i];

        cout << "U " << d + 1 << " " << i + 1 << "\n";

        cout << "P\n";
    }
}
