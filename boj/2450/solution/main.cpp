#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> shapes(N);
    vector<int> count(4, 0);

    for (int i = 0; i < N; ++i) {
        cin >> shapes[i];
        count[shapes[i]]++;
    }

    vector<vector<int>> permutations = {
        {1, 2, 3},
        {1, 3, 2},
        {2, 1, 3},
        {2, 3, 1},
        {3, 1, 2},
        {3, 2, 1}};

    int min_swaps = N;

    for (auto &order : permutations) {
        vector<int> region_start(4, 0);
        vector<int> region_end(4, 0);

        int index = 0;
        for (int i = 0; i < 3; ++i) {
            int shape = order[i];
            region_start[shape] = index;
            region_end[shape] = index + count[shape] - 1;
            index += count[shape];
        }

        vector<vector<int>> M(4, vector<int>(4, 0));

        for (int i = 0; i < N; ++i) {
            int shape = shapes[i];
            int region;
            for (int s = 1; s <= 3; ++s) {
                int start = region_start[order[s - 1]];
                int end = region_end[order[s - 1]];
                if (i >= start && i <= end) {
                    region = order[s - 1];
                    break;
                }
            }
            M[shape][region]++;
        }

        int swaps = 0;

        int direct_swaps = 0;
        for (int i = 1; i <= 3; ++i) {
            for (int j = i + 1; j <= 3; ++j) {
                int min_swap = min(M[i][j], M[j][i]);
                direct_swaps += min_swap;
                M[i][j] -= min_swap;
                M[j][i] -= min_swap;
            }
        }

        int remaining_mismatches = 0;
        for (int i = 1; i <= 3; ++i) {
            for (int j = 1; j <= 3; ++j) {
                if (i != j) {
                    remaining_mismatches += M[i][j];
                }
            }
        }

        int cycle_swaps = (remaining_mismatches * 2) / 3;

        swaps = direct_swaps + cycle_swaps;

        if (swaps < min_swaps) {
            min_swaps = swaps;
        }
    }

    cout << min_swaps << endl;

    return 0;
}
