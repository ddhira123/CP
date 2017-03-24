#include <bits/stdc++.h>
using namespace std;

const int LOWER_BOUND = 50;

int solve(vector<int> v) {
	sort(v.begin(), v.end());
	for(int i = 0 ; i < v.size() ; i++) {
		int iter = 0;
		bool ok = 1;
		for(int j = i ; j < v.size() ; j++) {
			int tot = 1;
			while(v[j] * tot < LOWER_BOUND && iter < i) {
				iter++;
				tot++;
			}

			if(v[j] * tot < LOWER_BOUND) {
				ok = 0;
				break;
			}
		}

		if(ok) {
			return v.size() - i;
		}
	}
	return 0;
}

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		int n; cin >> n;
		vector<int> v(n);

		for(int i = 0 ; i < n ; i++)
			cin >> v[i];

		cout << "Case #" << tc << ": " << solve(v) << "\n";
	}
	return 0;
}