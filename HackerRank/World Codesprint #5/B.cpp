#include <bits/stdc++.h>
using namespace std;

set<int> seen;
string s;

int main() {
	int n; cin >> n;
	for(int i = 0 ; i < n ; i++) {
		cin >> s;
		int ans = 0;
		for(char x : s) {
			if(seen.count(x)) continue;
			ans++;
			seen.insert(x);
		}
		cout << ans << endl;
		seen.clear();
	}
	return 0;
}