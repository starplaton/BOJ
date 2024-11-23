#include <bits/stdc++.h>
#define MAX_N 25
using namespace std;

int rows, cols, multiplier = 1, bitmask_limit, bitmask_map[1 << 20], dp[405][11000][2];
int MOD = 1e5;
char grid[MAX_N][MAX_N];

// Dynamic programming function to calculate possible states
int getDP(int position, int bitmask, bool carry) {
    int row = position / cols, col = position % cols, result = 0;
    if (position == rows * cols) return 1;  // Base case: reached end of grid
    if (dp[position][bitmask_map[bitmask]][carry] > -1)
        return dp[position][bitmask_map[bitmask]][carry];  // Memoized result

    // Transition logic based on current cell value
    if (grid[row][col] == 'J' || grid[row][col] == '?') {
        result += getDP(position + 1, bitmask << 1 & bitmask_limit, 1);
    }
    if (grid[row][col] == 'O' || grid[row][col] == '?') {
        result += getDP(position + 1, (bitmask | carry) << 1 & bitmask_limit, 0);
    }
    if (grid[row][col] == 'I' || grid[row][col] == '?') {
        if (!(bitmask >> (cols - 1) & 1) || col == cols - 1)
            result += getDP(position + 1, bitmask << 1 & bitmask_limit, 0);
    }
    return dp[position][bitmask_map[bitmask]][carry] = result % MOD;
}

// Precompute valid bitmask configurations
void preprocessBitmask() {
    int i, j, valid_count = 0;
    for (i = 0; i < 1 << 20; i += 2) {
        for (j = i; j > 1; j >>= 1)
            if ((j & 3) == 3) break;
        if (j < 2) bitmask_map[i] = valid_count++;
    }
}

int main() {
    int i, j;
    cin >> rows >> cols;
    bitmask_limit = (1 << cols) - 1;  // Generate bitmask limit for given columns
    memset(dp, -1, sizeof(dp));       // Initialize DP table with -1

    for (i = 0; i < rows; i++) {
        scanf("%s", &grid[i][0]);  // Input grid
        for (j = 0; j < cols; j++) {
            if (grid[i][j] == '?')
                multiplier = multiplier * 3 % MOD;  // Update multiplier for '?' cells
        }
    }

    preprocessBitmask();  // Precompute bitmask map
    // Calculate the result using DP and adjust by multiplier
    cout << (multiplier - getDP(0, 0, 0) + MOD) % MOD << endl;
    return 0;
}
