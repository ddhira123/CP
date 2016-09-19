#include <bits/stdc++.h>
using namespace std;

int n;
string s;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	cin >> s;

	long long ans = 0;
	for(int i = 0 ; i < n ; i++) {
		for(int ii = i ; ii < n ; ii++) {
			vector<char> v;
			bool ok = 1;

			for(int j = i ; j <= ii ; j++) {
				if(s[j] == ')' && (v.empty() || v.back() != '(')) {
					ok = 0;
					break;
				}
				else if(s[j] == ')' && v.back() == '(')
					v.pop_back();
				else
					v.push_back(s[j]);
			}

			ok &= v.empty();
			ans += ok;
		}
	}

	cout << ans << "\n";
	return 0;
}