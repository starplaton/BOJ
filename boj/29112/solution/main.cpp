#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 1000000007;

// 확장 유클리드 알고리즘을 사용하여 a와 b의 최대공약수와 x, y를 찾는 함수
ll extended_gcd_func(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extended_gcd_func(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// a의 모듈로 역원을 찾는 함수 (m과 a가 서로소일 때만 유효)
ll invmod(ll a, ll m) {
    ll x, y;
    ll g = extended_gcd_func(a, m, x, y);
    if (g != 1)
        return -1;  // 역원이 존재하지 않음
    else {
        ll res = (x % m + m) % m;
        return res;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m;
    cin >> n >> m;

    string S;
    cin >> S;

    // Compute prefix_mod[i] = S[1..i] mod m
    vector<ll> prefix_mod(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        prefix_mod[i] = (prefix_mod[i - 1] * 10 + (S[i - 1] - '0')) % m;
    }

    // Compute pow10[i] = 10^i mod m
    vector<ll> pow10(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        pow10[i] = (pow10[i - 1] * 10) % m;
    }

    // Initialize frequency array
    // freq[val] = number of j's with (prefix_mod[j] * pow10[j]) mod m == val
    vector<ll> freq(m, 0);
    // Initially, j=0
    ll initial_val = (prefix_mod[0] * pow10[0]) % m;
    freq[initial_val] = 1;

    // Initialize dp
    // We don't need to store the entire dp array, just accumulate the result
    // But to compute dp[i], we need to keep a running total
    // So, we can compute dp[i} on the fly
    ll dp = 0;
    ll answer = 0;

    for (int i = 1; i <= n; i++) {
        ll g = gcd(pow10[i], m);
        if (prefix_mod[i] % g != 0) {
            dp = 0;
        } else {
            ll m_prime = m / g;
            ll pow10_prime = pow10[i] / g;
            ll prefix_mod_prime = prefix_mod[i] / g;
            if (gcd(pow10_prime, m_prime) == 1) {
                ll inv = invmod(pow10_prime, m_prime);
                if (inv == -1) {
                    dp = 0;
                } else {
                    ll c = (prefix_mod_prime * inv) % m_prime;
                    dp = freq[c] % MOD;
                }
            } else {
                dp = 0;
            }
        }
        answer = (answer + dp) % MOD;
        // Update frequency
        ll freq_val = (prefix_mod[i] * pow10[i]) % m;
        freq[freq_val] = (freq[freq_val] + dp) % MOD;
    }

    cout << answer;
    return 0;
}
