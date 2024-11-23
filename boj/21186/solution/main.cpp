#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }

    // Step 1: Find the last occurrence of each number from 1 to k
    vector<int> last_pos(k + 1, -1);  // 1-based indexing
    for (int i = 0; i < n; ++i) {
        last_pos[x[i]] = i;
    }

    // Step 2: Use a stack to build the lex smallest subsequence
    vector<int> stack_seq;
    vector<bool> in_stack_flag(k + 1, false);  // Track if a number is in the stack

    for (int i = 0; i < n; ++i) {
        int current = x[i];

        // If the current number is already in the stack, skip it
        if (in_stack_flag[current]) {
            continue;
        }

        // While stack is not empty, and current number is smaller than the last in stack,
        // and the last number in stack appears again later
        while (!stack_seq.empty() && current < stack_seq.back() && i < last_pos[stack_seq.back()]) {
            // Remove the last number from stack
            in_stack_flag[stack_seq.back()] = false;
            stack_seq.pop_back();
        }

        // Add the current number to the stack
        stack_seq.push_back(current);
        in_stack_flag[current] = true;
    }

    // Step 3: Output the stack as the lex smallest subsequence
    for (int i = 0; i < stack_seq.size(); ++i) {
        cout << stack_seq[i];
        if (i != stack_seq.size() - 1) {
            cout << ' ';
        }
    }
}
