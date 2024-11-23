#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Memoization table
ll memo[20][4][2][2];

// Digits of the number
ll digits[20];
int num_digits;

// N value
ll N;

// DP function to count numbers containing '666'
ll dp(int pos, int count, bool is_tight, bool is_found) {
    if (pos == num_digits) {
        return is_found ? 1 : 0;
    }
    if (memo[pos][count][is_tight][is_found] != -1) {
        return memo[pos][count][is_tight][is_found];
    }
    ll res = 0;
    int limit = is_tight ? digits[pos] : 9;
    for (int d = 0; d <= limit; d++) {
        bool next_tight = is_tight && (d == digits[pos]);
        bool next_found = is_found;
        int next_count = count;
        if (d == 6) {
            next_count = count + 1;
            if (next_count >= 3) {
                next_found = true;
            }
        } else {
            next_count = 0;
        }
        // Ensure count doesn't exceed 3 for memoization
        if (next_count > 3) next_count = 3;
        res += dp(pos + 1, next_count, next_tight, next_found);
    }
    return memo[pos][count][is_tight][is_found] = res;
}

// Function to count numbers <= x that contain '666'
ll count666(ll x) {
    // Split x into digits
    num_digits = 0;
    ll temp = x;
    if (temp == 0) {
        digits[num_digits++] = 0;
    }
    while (temp > 0) {
        digits[num_digits++] = temp % 10;
        temp /= 10;
    }
    // Reverse to make digits[0] the most significant digit
    for (int i = 0; i < num_digits / 2; i++) {
        swap(digits[i], digits[num_digits - i - 1]);
    }
    // Initialize memoization table
    memset(memo, -1, sizeof(memo));
    // Start DP
    return dp(0, 0, true, false);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    ll left = 666;
    ll right = 10LL * 1000000000;  // 1e10 is sufficiently large
    ll answer = -1;

    while (left <= right) {
        ll mid = left + (right - left) / 2;
        ll cnt = count666(mid);
        if (cnt >= N) {
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << answer;
    return 0;
}
