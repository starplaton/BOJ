#include <bits/stdc++.h>
using namespace std;

struct Job {
    long long M;
    long long P;
    long long R;
};

// Comparator for sorting jobs based on Smith's Rule (Ri / Pi)
bool compare_jobs(const Job &a, const Job &b) {
    return a.R * b.P < b.R * a.P;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    long long T;
    cin >> N >> T;

    vector<long long> M(N);
    for (auto &x : M) cin >> x;

    vector<long long> P(N);
    for (auto &x : P) cin >> x;

    vector<long long> R(N);
    for (auto &x : R) cin >> x;

    vector<Job> jobs(N);
    for (int i = 0; i < N; i++) {
        jobs[i] = Job{M[i], P[i], R[i]};
    }

    // Sort jobs based on Smith's Rule
    sort(jobs.begin(), jobs.end(), compare_jobs);

    // Initialize DP arrays
    const long long NEG_INF = -1e18;
    vector<long long> dp_prev(T + 1, NEG_INF);
    dp_prev[0] = 0;

    // Iterate through each job
    for (int i = 0; i < N; i++) {
        vector<long long> dp_next = dp_prev;  // Copy previous state
        for (long long t = 0; t <= T - jobs[i].R; t++) {
            if (dp_prev[t] != NEG_INF) {
                long long new_t = t + jobs[i].R;
                if (new_t <= T) {
                    long long temp = dp_prev[t] + jobs[i].M - jobs[i].P * new_t;
                    if (temp > dp_next[new_t]) {
                        dp_next[new_t] = temp;
                    }
                }
            }
        }
        dp_prev = move(dp_next);  // Update DP for the next iteration
    }

    // Find the maximum score achievable within time T
    long long answer = 0;
    for (long long t = 0; t <= T; t++) {
        if (dp_prev[t] > answer) {
            answer = dp_prev[t];
        }
    }
    cout << max(answer, (long long)0);
}
