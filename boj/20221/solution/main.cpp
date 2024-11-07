#include<cassert>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

#define pb push_back

void stop() { puts("impossible"); exit(0); }

int main() {
	string last = "", cur;
	int n;
	vector<string> output;

	cin >> n;
	getline(cin, cur);

	while (n--) {
		getline(cin, cur);
		for (char &c : cur) if (c == '9') c = '6';

		if (last.size() > cur.size()) stop();

		if (last.size() < cur.size()) {
			output.pb(last = cur);
			continue;
		}

		vector<int> sixes, nines;
		for (int i = 0; i < (int) cur.size(); i++) {
			if (last[i] < cur[i]) {
				break; // all is fine.
			} else if (last[i] == cur[i]) {
				if (cur[i] == '6') sixes.pb(i);
			} else {
				assert(last[i] > cur[i]);

				if (cur[i] == '6') {
					// smallest increment possible:
					cur[i] = '9';
					nines.pb(i);
					if (last[i] < '9') break;
				} else {
					// change the last '6' to a '9'
					if (sixes.empty()) stop();

					int j = sixes.back();
					sixes.pop_back();
					cur[j] = '9';

					while (!nines.empty() && nines.back() > j) {
						cur[nines.back()] = '6';
						nines.pop_back();
					}
					// now last[i] < cur[i]
					break;
				}
			}
		}

		output.pb(last = cur);
	}

	printf("possible\n");
	for (string &s : output) {
		printf("%s\n", s.c_str());
	}

	return 0;
}
