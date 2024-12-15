#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int K;
    cin >> K;
    // Precompute divisors for each number up to K
    vector<vector<int>> divisors(K + 1, vector<int>());
    for (int d = 1; d <= K; d++) {
        for (int multiple = d; multiple <= K; multiple += d) {
            divisors[multiple].push_back(d);
        }
    }
    // Initialize dp array
    // dp[i] = true if the current player can force a win from i
    vector<bool> dp(K + 2, false);  // dp[K+1] is unused
    // Iterate from K down to 1
    for (int i = K; i >= 1; i--) {
        for (auto &d : divisors[i]) {
            int j = i + d;
            if (j > K) {
                // This move causes player to lose, so skip
                continue;
            }
            if (!dp[j]) {
                dp[i] = true;
                break;
            }
        }
        // If no move leads to a losing position for opponent, dp[i] remains false
    }
    if (dp[1]) {
        cout << "Kali";
    } else {
        cout << "Ringo";
    }
}
