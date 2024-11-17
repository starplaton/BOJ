#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;

int main() {
    int N;
    cin >> N;

    // Special case when N is 0 (though N >=1 in constraints)
    if (N == 0) {
        cout << "0\n";
        return 0;
    }

    // dp[pos][mod3]: number of pos-digit numbers with sum mod3 = mod3
    // Only need to keep current and next states
    vector<long long> dp_prev(3, 0);
    vector<long long> dp_curr(3, 0);

    // Initial state: 0 digits, sum mod3 =0
    dp_prev[0] = 1;

    // Iterate over the first N-1 digits
    for (int pos = 0; pos < N - 1; pos++) {
        // Reset current state
        fill(dp_curr.begin(), dp_curr.end(), 0);

        for (int mod = 0; mod < 3; mod++) {
            if (dp_prev[mod] == 0) continue;

            // Add digit 1
            int new_mod1 = (mod + 1) % 3;
            dp_curr[new_mod1] = (dp_curr[new_mod1] + dp_prev[mod]) % MOD;

            // Add digit 5
            int new_mod5 = (mod + 5) % 3;
            dp_curr[new_mod5] = (dp_curr[new_mod5] + dp_prev[mod]) % MOD;
        }

        // Update dp_prev for next position
        dp_prev = dp_curr;
    }

    // After N-1 digits, we need sum ≡1 mod3
    // Then add last digit 5 (which adds 5 to the sum, making total sum ≡ (1+2)=0 mod3)
    // So the number is valid if sum of first N-1 digits ≡1 mod3

    // If N ==1, there are no first N-1 digits, sum=0
    // To make total sum ≡0 mod3, we need 0 +5 ≡2≡0? No, thus N=1 needs to be handled as dp_prev should represent sum=0
    // But according to our DP, dp_prev[1] holds the number of first N-1 digits with sum ≡1 mod3

    long long answer = 0;
    if (N == 1) {
        // Only one digit: 5
        // Check if 5 is divisible by 15
        // 5 is not divisible by 15
        answer = 0;
    } else {
        answer = dp_prev[1];
    }

    cout << answer << "\n";

    return 0;
}
