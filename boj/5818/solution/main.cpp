#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;

    // Initialize cost matrix with 0s
    // Nodes are from 0 to N, where 0 is the virtual node
    vector<vector<int>> cost(N + 1, vector<int>(N + 1, 0));

    // Read meeting costs
    for (int k = 1; k <= N; k++) {
        for (int m = 1; m <= N; m++) {
            cin >> cost[k][m];
        }
    }

    // Read Mk costs
    vector<int> Mk(N + 1, 0);  // Mk[1] to Mk[N]
    for (int k = 1; k <= N; k++) cin >> Mk[k];

    // Connect virtual node 0 to all spies with cost Mk[k]
    for (int k = 1; k <= N; k++) {
        cost[0][k] = Mk[k];
        cost[k][0] = Mk[k];
    }

    // Prim's algorithm
    vector<bool> in_mst(N + 1, false);
    vector<int> min_cost_vec(N + 1, INT32_MAX);
    min_cost_vec[0] = 0;
    for (int k = 1; k <= N; k++) {
        min_cost_vec[k] = cost[0][k];
    }

    ll total_cost = 0;

    for (int i = 0; i <= N; i++) {
        // Find the node u not in MST with the smallest min_cost
        int u = -1;
        int smallest = INT32_MAX;
        for (int v = 0; v <= N; v++) {
            if (!in_mst[v] && min_cost_vec[v] < smallest) {
                smallest = min_cost_vec[v];
                u = v;
            }
        }

        if (u == -1) {
            break;  // All nodes are included
        }

        // Add the smallest cost to total_cost
        total_cost += smallest;
        in_mst[u] = true;

        // Update the min_cost for all vertices not yet in MST
        for (int v = 0; v <= N; v++) {
            if (!in_mst[v]) {
                if (cost[u][v] < min_cost_vec[v]) {
                    min_cost_vec[v] = cost[u][v];
                }
            }
        }
    }

    cout << total_cost;
}
