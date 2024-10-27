#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 함수: 대회 수 k가 가능한지 확인
bool isPossible(ll k, ll E, ll EM, ll M, ll MH, ll H) {
    // 쉬운 문제 할당
    if (E + EM < k) return false;
    ll used_EM_for_E = max(0LL, k - E);
    if (used_EM_for_E > EM) return false;

    // 어려운 문제 할당
    if (H + MH < k) return false;
    ll used_MH_for_H = max(0LL, k - H);
    if (used_MH_for_H > MH) return false;

    // 중간 문제 할당
    // 남은 EM과 MH
    ll remaining_EM = EM - used_EM_for_E;
    ll remaining_MH = MH - used_MH_for_H;

    // 중간 문제에 할당 가능한 총 문제 수
    ll total_M = M + remaining_EM + remaining_MH;

    if (total_M < k) return false;

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll E, EM, M, MH, H;
    cin >> E >> EM >> M >> MH >> H;

    // 이진 탐색 범위 설정
    ll left = 0;
    ll right = E + EM + M + MH + H;
    ll answer = 0;

    while (left <= right) {
        ll mid = left + (right - left) / 2;
        if (isPossible(mid, E, EM, M, MH, H)) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << answer;
}
