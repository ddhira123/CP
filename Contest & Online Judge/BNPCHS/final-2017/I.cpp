#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		cout << "Kasus #" << tc << ":\n";
		int n; cin >> n;

		set<vector<pair<int,int>>> s;

		for(int i = 0 ; i < n ; i++) {
			vector<pair<int,int>> v;
			for(int j = 0 ; j < 3 ; j++) {
				pair<int,int> x;
				cin >> x.first >> x.second;
				v.push_back(x);
			}

			if(!s.count(v)) {
				for(int j = 0 ; j < 3 ; j++) {
					pair<int,int> x = v[j];

					printf("%d %d%c", x.first, x.second, j==2 ? '\n' : ' ');
				}
				sort(v.begin(), v.end());
				do {
					s.insert(v);
				} while(next_permutation(v.begin(), v.end()));
			}
		}
	}
	return 0;
}