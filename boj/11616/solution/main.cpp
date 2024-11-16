#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    string S;
    cin >> S;

    // Compute prefix_mod[i] = S[1..i] mod m
    vector<int> prefix_mod(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        prefix_mod[i] = ((ll)prefix_mod[i - 1] * 10 + (S[i - 1] - '0')) % m;
    }

    if (__gcd(m, 10) == 1) {
        // Compute power10[i] = 10^i mod m
        vector<int> power10(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            power10[i] = ((ll)power10[i - 1] * 10) % m;
        }

        // Compute transformed_mod[i] = (prefix_mod[i] * power10[i]) mod m
        vector<int> transformed_mod(n + 1, 0);
        for (int i = 0; i <= n; i++) {
            transformed_mod[i] = ((ll)prefix_mod[i] * power10[i]) % m;
        }

        // Initialize frequency array
        // freq[val] = number of j's with transformed_mod[j] == val
        // Initialize freq[transformed_mod[0]] +=1
        vector<ll> freq(m, 0);
        freq[transformed_mod[0]] += 1;

        // Initialize answer
        ll answer = 0;

        // Iterate through the string
        for (int i = 1; i <= n; i++) {
            // dp[i] is the number of ways to partition S[1..i]
            ll dp_i = freq[transformed_mod[i]];
            dp_i %= MOD;
            // Update frequency
            freq[transformed_mod[i]] += dp_i;
            freq[transformed_mod[i]] %= MOD;
            // If it's the last character, store the answer
            if (i == n) {
                answer = dp_i;
            }
        }

        cout << answer;

    } else {
        // When m shares factors with 10
        // dp[i] = (prefix_mod[i] ==0) ? cum_dp[i-1} :0
        // cum_dp[i] = cum_dp[i-1} + dp[i} mod MOD

        ll cum_sum = 1;  // cum_sum up to i-1. dp[0] =1
        ll dp_i = 0;
        ll answer = 0;

        for (int i = 1; i <= n; i++) {
            if (prefix_mod[i] == 0) {
                dp_i = cum_sum;
            } else {
                dp_i = 0;
            }
            dp_i %= MOD;
            cum_sum = (cum_sum + dp_i) % MOD;
            if (i == n) {
                answer = dp_i;
            }
        }

        cout << answer;
    }

    return 0;
}
