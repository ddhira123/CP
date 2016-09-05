#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		int n, m; cin >> n >> m;
		string s; cin >> s;
		m--;

		vector<int> diff;
		int tot = 0;
		int ans = 1e9;
		if(m <= n-m-1) {
			for(int i = 0 ; i < n-i-1 ; i++) {
				if(s[i] == s[n-i-1]) continue;
				diff.push_back(i);
				int a = (int)s[i];
				int b = (int)s[n-i-1];
				int dst = max(a,b) - min(a,b);
				dst = min(dst,26 - dst);
				tot += dst;
			}
			if(diff.size() == 0) {
				ans = 0;
			}
			else if(diff.back() <= m) {
				ans = tot + m - diff[0];
			}
			else if(diff[0] <= m) {
				int a = diff.back() - m;
				int b = m - diff[0];
				ans = tot + a + b + min(a,b);
			}
			else {
				ans = tot + diff.back() - m;
			}
		}
		else {
			for(int i = 0 ; i < n-i-1 ; i++) {
				if(s[i] == s[n-i-1]) continue;
				diff.push_back(n-i-1);
				int a = (int)s[i];
				int b = (int)s[n-i-1];
				int dst = max(a,b) - min(a,b);
				dst = min(dst,26 - dst);
				tot += dst;
			}
			if(diff.size() == 0) {
				ans = 0;
			}
			else if(diff.back() >= m) {
				ans = tot + diff[0] - m;
			}
			else if(diff[0] >= m) {
				int a = diff[0] - m;
				int b = m - diff.back();
				ans = tot + a + b + min(a,b);
			}
			else {
				ans = tot + m - diff.back();
			}
		}

		cout << ans << "\n";
	}
	return 0;
}