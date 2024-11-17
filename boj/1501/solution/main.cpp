#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Dictionary to store word mappings
    unordered_map<string, unordered_map<string, int>> dict;

    int N;
    cin >> N;
    string word;

    // Read N dictionary words
    for (int i = 0; i < N; i++) {
        cin >> word;

        if (word.length() <= 2) {
            // Case for words of length <= 2
            string key = word;
            if (dict[key][""] > 0) {
                dict[key][""]++;
            } else {
                dict[key][""] = 1;
            }
        } else {
            // Case for words of length > 2
            string first_k = word[0] + word.substr(word.length() - 1, 1);
            string middle = word.substr(1, word.length() - 2);
            sort(middle.begin(), middle.end());
            if (dict[first_k][middle] > 0) {
                dict[first_k][middle]++;
            } else {
                dict[first_k][middle] = 1;
            }
        }
    }

    int M;
    cin >> M;
    cin.ignore();  // Consume newline character after M

    // Process M sentences
    for (int i = 0; i < M; i++) {
        string sentence;
        getline(cin, sentence);

        stringstream ss(sentence);
        string w;
        long long count = 1;
        bool isCan = false;

        while (ss >> w) {
            int temp = 0;

            if (w.length() <= 2) {
                // Case for words of length <= 2
                string key = w;
                if (dict[key].count("") > 0) {
                    temp += dict[key][""];
                }
            } else {
                // Case for words of length > 2
                string first_k = w[0] + w.substr(w.length() - 1, 1);
                string middle = w.substr(1, w.length() - 2);
                sort(middle.begin(), middle.end());
                if (dict[first_k].count(middle) > 0) {
                    temp += dict[first_k][middle];
                }
            }

            if (temp != 0) {
                count *= temp;
                isCan = true;
            }
        }

        if (!isCan) {
            count = 0;
        }
        cout << count << "\n";
    }

    return 0;
}
