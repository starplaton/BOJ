#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int c;
    cin >> c;
    while (c--) {
        int d, n;
        cin >> d >> n;
        // To handle large d, use vector with size d
        // Initialize frequency vector with 0
        // To save space and speed, use vector<int> freq with d elements
        // Initialize all to 0
        // Set freq[0] =1
        vector<int> freq(d, 0);
        freq[0] = 1;
        ll prefix_sum = 0;
        ll count = 0;
        for (int i = 0; i < n; i++) {
            ll num;
            cin >> num;
            prefix_sum += num;
            ll current_mod = prefix_sum % d;
            // Since all numbers are positive, current_mod is already in [0, d-1]
            count += freq[current_mod];
            freq[current_mod]++;
        }
        cout << count << "\n";
    }

    return 0;
}
