#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll N, K, T;
    cin >> N >> K >> T;
    vector<ll> A(N);
    ll S = 0;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        S += A[i];
    }
    if (S % K != 0) {
        cout << "NO";
        return 0;
    }
    ll M = S / K;
    if (M > N) {
        cout << "NO";
        return 0;
    }
    sort(A.begin(), A.end(), greater<ll>());
    ll sum_top_M = 0;
    for (int i = 0; i < M; i++) sum_top_M += A[i];
    ll required_moves = K * M - sum_top_M;
    if (required_moves <= T) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}
