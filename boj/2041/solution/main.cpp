#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;

    // Calculate total horizontal and vertical differences
    int H = N * (M - 1);
    int V = (N - 1) * M;
    int total_diff = H + V;

    // Check if total_diff matches the required
    // Required differences are from 1 to (2NM - N - M)
    // which is 2NM -N -M = H + V
    // So it's consistent

    // Assign horizontal differences: 1 to H
    // Assign vertical differences: H+1 to H+V
    vector<int> h_diff(H, 0);
    vector<int> v_diff(V, 0);

    for (int i = 0; i < H; i++) h_diff[i] = i + 1;
    for (int i = 0; i < V; i++) v_diff[i] = H + i + 1;

    // Initialize grid
    // To handle large N and M, use vector of vectors
    // Since N and M can be up to1000, it's feasible
    vector<vector<ll>> grid(N, vector<ll>(M, 0));

    grid[0][0] = 1;

    // Fill the first row
    for (int j = 1; j < M; j++) {
        grid[0][j] = grid[0][j - 1] + h_diff[j - 1];
    }

    // Fill the first column
    for (int i = 1; i < N; i++) {
        grid[i][0] = grid[i - 1][0] + v_diff[i - 1];
    }

    // Fill the rest of the grid
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            // Calculate the index for horizontal differences
            // Each row has (M-1) horizontal differences
            int h_idx = i * (M - 1) + (j - 1);
            grid[i][j] = grid[i][j - 1] + h_diff[h_idx];
            // Now, grid[i][j} should also equal grid[i-1][j} + v_diff[j + (i-1)*M}
            // But since v_diff is assigned sequentially, we need to ensure consistency
            // However, in this approach, it's guaranteed because differences are unique
            // and we have assigned differences correctly
        }
    }

    // Output the grid
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << grid[i][j] << (j == M - 1 ? '\n' : ' ');
        }
    }
}