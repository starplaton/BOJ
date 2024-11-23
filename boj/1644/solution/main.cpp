#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    if (N < 2) {
        // The smallest prime is 2
        cout << "0";
        return 0;
    }

    // Sieve of Eratosthenes to find all primes up to N
    vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= N; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
    }

    // Collect all primes up to N in a list
    vector<int> primes;
    for (int i = 2; i <= N; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    // Two-pointer technique to find all sequences of consecutive primes summing to N
    int count = 0;
    int start = 0, end = 0;
    ll current_sum = 0;

    while (true) {
        if (current_sum >= N) {
            if (current_sum == N) {
                count++;
            }
            current_sum -= primes[start];
            start++;
        } else {
            if (end == primes.size()) {
                break;
            }
            current_sum += primes[end];
            end++;
        }
    }

    cout << count;
}
