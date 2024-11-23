#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAX_N = 10;
const int MAX_T = 100;

long long dp[MAX_N + 1][MAX_T + 1][MAX_T + 1][MAX_T + 1];

long long solve(int level, int red, int green, int blue) {
    if (level == 0) return 1; // Base case: no more levels to decorate
    if (dp[level][red][green][blue] != -1) return dp[level][red][green][blue];

    long long ways = 0;
    int total = level * (level + 1) / 2; // Total number of toys needed up to this level

    // Try all combinations of red, green, and blue toys for this level
    for (int r = 0; r <= level; ++r) {
        for (int g = 0; g <= level - r; ++g) {
            int b = level - r - g;
            if (r <= red && g <= green && b <= blue) {
                ways += solve(level - 1, red - r, green - g, blue - b);
            }
        }
    }

    return dp[level][red][green][blue] = ways;
}

int main() {
    int N, R, G, B;
    cin >> N >> R >> G >> B;

    memset(dp, -1, sizeof(dp));

    long long result = solve(N, R, G, B);
    cout << result << endl;

    return 0;
}
