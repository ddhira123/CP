#include <bits/stdc++.h>
using namespace std;

char ans[1005];
string s, t;
int cnt;

int main() {
	cin >> s >> t;
	for(int i = 0 ; i < s.length() ; i++) {
		if(s[i] != t[i]) {
			if(ans[s[i]] != 0 && ans[s[i]] != t[i]) {
				cout << "-1\n";
				return 0;
			}
			if(ans[t[i]] != 0 && ans[t[i]] != s[i]) {
				cout << "-1\n";
				return 0;
			}
			if(ans[s[i]] != 0) continue;
			cnt++;
			ans[s[i]] = t[i];
			ans[t[i]] = s[i];
		}
		else {
			if(ans[s[i]] != 0 && ans[s[i]] != t[i]) {
				cout << "-1\n";
				return 0;
			}
			if(ans[s[i]] != 0) continue;
			//cnt++;
			ans[s[i]] = t[i];
			ans[t[i]] = s[i];
		}
	}
	cout << cnt << "\n";
	for(char c = 'a' ; c <= 'z' ; c++) {
		if(ans[c] != 0 && ans[c] > c)
			cout << c << " " << ans[c] << "\n";
	}
	return 0;
}