#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (true) {
        int N;
        cin >> N;
        if (N == 0) break;

        vector<int> heights(N);
        for (int &h : heights) cin >> h;

        sort(heights.begin(), heights.end());

        // Traverse sorted heights and count frequencies
        int max_freq = 1;
        int current_freq = 1;
        for (int i = 1; i < N; ++i) {
            if (heights[i] == heights[i - 1]) {
                current_freq++;
                if (current_freq > max_freq) {
                    max_freq = current_freq;
                }
            } else {
                current_freq = 1;
            }
        }

        cout << max_freq << "\n";
    }

    return 0;
}
