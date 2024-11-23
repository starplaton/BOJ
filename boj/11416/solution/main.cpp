#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Function to get all unique divisors of a number
vector<ll> get_divisors(ll num) {
    vector<ll> divisors;
    num = abs(num);
    for (ll i = 1; i * i <= num; ++i) {
        if (num % i == 0) {
            divisors.push_back(i);
            if (i != num / i) {
                divisors.push_back(num / i);
            }
        }
    }
    // Include negative divisors
    int original_size = divisors.size();
    for (int i = 0; i < original_size; ++i) {
        divisors.push_back(-divisors[i]);
    }
    // Remove duplicates if any
    sort(divisors.begin(), divisors.end());
    divisors.erase(unique(divisors.begin(), divisors.end()), divisors.end());
    return divisors;
}

// Function to evaluate polynomial at x = p
ll evaluate_poly(ll p, const vector<ll> &poly) {
    ll result = 0;
    for (auto coeff : poly) {
        result = result * p + coeff;
    }
    return result;
}

// Function to divide polynomial by (x - p), assuming p is a root
// Returns the new polynomial after division
vector<ll> divide_poly(ll p, const vector<ll> &poly) {
    int n = poly.size();
    vector<ll> new_poly(n - 1, 0);
    new_poly[0] = poly[0];  // Leading coefficient
    for (int i = 1; i < n - 1; ++i) {
        new_poly[i] = poly[i] + new_poly[i - 1] * p;
    }
    // The last term is poly[n-1] + new_poly[n-2] * p, which should be 0
    return new_poly;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<ll> coefficients(n);  // c_{n-1} to c0
    for (int i = 0; i < n; ++i) {
        cin >> coefficients[i];
    }

    // Build the polynomial: x^n + c_{n-1}x^{n-1} + ... + c0
    vector<ll> poly(n + 1, 0);
    poly[0] = 1;  // Coefficient for x^n
    for (int i = 0; i < n; ++i) {
        poly[i + 1] = coefficients[i];
    }

    ll c0 = poly.back();
    // Get all possible integer roots
    vector<ll> divisors = get_divisors(c0);

    ll rational_root_count = 0;

    // Since we will modify the polynomial, make a copy
    vector<ll> current_poly = poly;

    for (auto p : divisors) {
        // Check if p is a root multiple times
        while (current_poly.size() > 1 && evaluate_poly(p, current_poly) == 0) {
            rational_root_count++;
            // Divide the polynomial by (x - p)
            current_poly = divide_poly(p, current_poly);
        }
    }

    // The number of irrational roots is n - rational_root_count
    ll irrational_roots = n - rational_root_count;
    cout << irrational_roots;
}
