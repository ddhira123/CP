#include <bits/stdc++.h>
using namespace std;

string s;
int t;

int main() {
	cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		cin >> s;
		int ans = 1e9;
		for(int times = 0 ; times < 2 ; times++) {
			int ret = s[0] == '-' ? 1 : 0;

			for(int i = 1 ; i < s.length() ; i++)
				ret += 2 * (s[i] == '-' && s[i-1] == '+');

			ans = min(ans,times + ret);

			for(int i = 0 ; i < s.length() ; i++)
				s[i] = (s[i] == '-') ? '+' : '-';
			reverse(s.begin(),s.end());
		}
		printf("Case #%d: %d\n",tc,ans);
	}
	return 0;
}