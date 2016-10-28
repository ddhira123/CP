#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		string s; cin >> s;
		int len = s.length();
		while(len > 1 && len % 2 == 0) len /= 2;
		bool ok = len == 1;
		if(ok) {
			for(int i = 1 ; i < s.length() ; i += 2)
				ok &= ((s[i] == 'P' || s[i-1] == 'P'));
		}

		if(ok) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}