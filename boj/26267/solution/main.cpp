#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<pair<ll, ll>> banks(N);
    for (int i = 0; i < N; i++) {
        ll X, T, C;
        cin >> X >> T >> C;
        ll S = X - T;
        banks[i] = {S, C};
    }

    sort(banks.begin(), banks.end());

    ll max_sum = 0;
    ll current_S = banks[0].first;
    ll current_sum = 0;

    for (int i = 0; i < N; i++) {
        if (banks[i].first != current_S) {
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
            current_S = banks[i].first;
            current_sum = banks[i].second;
        } else {
            current_sum += banks[i].second;
        }
    }
    // Check last group
    if (current_sum > max_sum) {
        max_sum = current_sum;
    }

    cout << max_sum;
}
