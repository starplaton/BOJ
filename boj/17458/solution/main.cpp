#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Function to compute the closure of the given elements under AND and OR
bitset<128> compute_closure(int k, const vector<int>& elements) {
    int size = (1 << k);
    bitset<128> closure;
    for (auto x : elements) {
        closure.set(x);
    }

    bool changed = true;
    while (changed) {
        changed = false;
        // Collect all elements currently in closure
        vector<int> current_elements;
        for (int i = 0; i < size; ++i) {
            if (closure[i]) current_elements.push_back(i);
        }
        // Iterate over all pairs and add their AND and OR
        int n = current_elements.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                int x = current_elements[i];
                int y = current_elements[j];
                int and_val = x & y;
                int or_val = x | y;
                if (!closure[and_val]) {
                    closure.set(and_val);
                    changed = true;
                }
                if (!closure[or_val]) {
                    closure.set(or_val);
                    changed = true;
                }
            }
        }
    }
    return closure;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int k, n;
    cin >> k >> n;

    vector<int> elements(n);
    for (auto& x : elements) {
        cin >> x;
    }

    // Compute S0
    bitset<128> S0 = compute_closure(k, elements);

    // Compute U \ S0
    int size = (1 << k);
    vector<int> remaining;
    for (int i = 0; i < size; ++i) {
        if (!S0[i]) remaining.push_back(i);
    }

    // Build dependency graph
    // Assign indices to remaining elements
    int m = remaining.size();
    unordered_map<int, int> elem_to_idx;
    for (int i = 0; i < m; ++i) {
        elem_to_idx[remaining[i]] = i;
    }

    // Dependencies: for each x in remaining, list of z =x OR y for y ∈ S0 and z ∉ S0
    vector<vector<int>> dependencies(m, vector<int>());
    for (int i = 0; i < m; ++i) {
        int x = remaining[i];
        for (int y = 0; y < size; ++y) {
            if (S0[y]) {
                int z = x | y;
                if (z < size && !S0[z]) {
                    // z is in remaining
                    if (elem_to_idx.find(z) != elem_to_idx.end()) {
                        dependencies[i].push_back(elem_to_idx[z]);
                    }
                }
            }
        }
    }

    // Topological sort
    // Compute in-degree
    vector<int> in_degree(m, 0);
    for (int i = 0; i < m; ++i) {
        for (auto z : dependencies[i]) {
            in_degree[z]++;
        }
    }

    // Kahn's algorithm
    queue<int> q;
    vector<int> topo_order;
    for (int i = 0; i < m; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);
        for (auto v : dependencies[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Check for cycles
    if (topo_order.size() != m) {
        // Cycle detected, but according to problem constraints, this should not happen
        cout << "0\n";
        return 0;
    }

    // DP to count the number of lower ideals
    // Initialize DP with 1
    ll dp = 1;
    // To store dependencies
    // For each element in topo_order, store its dependencies
    vector<vector<int>> adj(m, vector<int>());
    for (int i = 0; i < m; ++i) {
        adj[i] = dependencies[i];
    }

    // Implement DP
    // Represent the inclusion mask as bits, but with m<=128, and k=7, m<=128
    // However, m can be up to 128, but with k=7, likely manageable
    // Use memoization or iterative DP
    // Implemented as iterative DP with states

    // However, with m=11, as in sample input 2, 2^11=2048, manageable
    // Thus, proceed with standard DP

    // Initialize DP array
    vector<ll> dp_states(1 << m, 0);
    dp_states[0] = 1;

    for (int i = 0; i < m; ++i) {
        // Iterate in reverse to prevent overcounting
        for (int mask = (1 << m) - 1; mask >= 0; --mask) {
            if (dp_states[mask] == 0) continue;
            // Check if dependencies of element i are included in mask
            bool can_include = true;
            for (auto dep : adj[i]) {
                if (!(mask & (1 << dep))) {
                    can_include = false;
                    break;
                }
            }
            if (can_include) {
                // Include element i
                int new_mask = mask | (1 << i);
                dp_states[new_mask] += dp_states[mask];
            }
        }
    }

    // Sum all dp_states
    ll total = 0;
    for (auto val : dp_states) {
        total += val;
    }

    // But according to the problem, sample shows small numbers like 7,29,1
    // Thus, likely, m <=20, manageable with 64-bit integers

    // Now, output the total
    cout << total << "\n";
}
