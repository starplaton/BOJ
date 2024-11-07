#include <iostream>
#include <vector>
using namespace std;

int findNextPosition(const vector<bool>& isDead, int pos, int direction, int n) {
    int count = 0;
    do {
        pos += direction;
        if (pos >= n) pos = 0;
        if (pos < 0) pos = n - 1;
        count++;
        if (count > n) return -1;  // 모든 적이 죽었을 경우
    } while (isDead[pos]);
    return pos;
}

int solve(int n, int C, vector<int>& hp) {
    vector<int> health = hp;
    vector<bool> isDead(n, false);
    int pos = 0;
    int direction = 1;
    int attacks = n + 5;

    if (health[0] <= 0) {
        isDead[0] = true;
        int nextPos = findNextPosition(isDead, pos, direction, n);
        if (nextPos == -1) return 1;  // 모든 적이 죽었다면 현재 위치 반환
        pos = nextPos;
    }

    while (attacks > 0) {
        attacks--;

        // 현재 적의 체력 감소
        health[pos] -= C;

        // 마지막 공격이었다면 현재 위치 반환
        if (attacks == 0) {
            return pos + 1;
        }

        // 적이 죽었는지 확인
        if (health[pos] <= 0 && !isDead[pos]) {
            isDead[pos] = true;
            direction *= -1;  // 방향 전환
        }

        // 다음 유효한 위치 찾기
        int nextPos = findNextPosition(isDead, pos, direction, n);

        // 모든 적이 죽었다면 현재 위치 반환
        if (nextPos == -1) {
            return pos + 1;
        }

        pos = nextPos;
    }

    return pos + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, C;
        cin >> n >> C;

        vector<int> hp(n);
        for (int i = 0; i < n; i++) {
            cin >> hp[i];
        }

        cout << solve(n, C, hp) << "\n";
    }

    return 0;
}