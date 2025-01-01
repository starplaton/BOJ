#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sf1(a) cin >> (a)
#define pf1l(a) cout << (a) << "\n"
#define pfvecl(V)                             \
    do {                                      \
        for (auto &t : (V)) cout << t << " "; \
        cout << "\n";                         \
    } while (0)
#define pb push_back
#define all(x) (x).begin(), (x).end()

vl ans;
vector<bool> sieve;

// n이 소수인지 확인(1~100000 범위면 sieve 이용, 그 이상은 직접 판별)
bool isPrime(ll n) {
    if (n <= 100000) return sieve[n];
    if (n == 1) return false;
    for (ll d = 2; d * d <= n; d++) {
        if (n % d == 0) return false;
    }
    return true;
}

// 재귀적으로 문제 풀이
void solve(int least, ll cur, ll N) {
    if (N - 1 <= least) return;
    if (isPrime(N - 1)) ans.pb(cur * (N - 1));

    for (int p = least; 1LL * p * p <= N; p++) {
        if (!isPrime(p)) continue;
        ll tot = p + 1, powP = p;
        while (true) {
            if (N == tot) {
                ans.pb(cur * powP);
                break;
            }
            if (N % tot == 0) {
                solve(p + 1, cur * powP, N / tot);
            }
            powP *= p;
            tot += powP;
            if (tot > N) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 에라토스테네스의 체 초기화
    sieve.resize(100001, true);
    sieve[0] = sieve[1] = false;
    rep(prime, 2, 1000) {
        if (!sieve[prime]) continue;
        for (int j = prime * prime; j <= 100000; j += prime) {
            sieve[j] = false;
        }
    }

    int T;
    sf1(T);
    while (T--) {
        ans.clear();
        ll N;
        sf1(N);

        // N이 1이면 별도 처리
        if (N == 1) {
            pf1l(1);
            continue;
        }
        // 문제 풀이 함수 호출
        solve(2, 1, N);

        // 결과가 없다면 "none!" 출력, 있으면 정렬 후 모두 출력
        if (ans.empty()) {
            pf1l("none!");
        } else {
            sort(all(ans));
            pfvecl(ans);
        }
    }
    return 0;
}
