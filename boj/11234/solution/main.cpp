#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> marbles(n);
    for (int i = 0; i < n; ++i) {
        cin >> marbles[i];
    }

    // Calculate the total number of marbles
    int totalMarbles = 0;
    for (int m : marbles) {
        totalMarbles += m;
    }

    // Calculate the maximum score
    int maxScore = 0;
    for (int i = 0; i < n - 1; ++i) {
        maxScore += abs(marbles[i] - marbles[i + 1]);
    }

    // Calculate the minimum number of moves
    int leftSum = 0;
    int minMoves = 0;
    for (int i = 0; i < n; ++i) {
        leftSum += marbles[i];
        int rightSum = totalMarbles - leftSum;
        minMoves += min(leftSum, rightSum);
    }

    cout << maxScore << " " << minMoves << endl;

    return 0;
}
