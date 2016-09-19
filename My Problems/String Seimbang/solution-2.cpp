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
		vector<char> v;

		for(int j = i ; j < n ; j++) {
			if(s[j] == ')' && (v.empty() || v.back() != '(')) {
				break;
			}
			else if(s[j] == ')' && v.back() == '(')
				v.pop_back();
			else
				v.push_back(s[j]);

			ans += v.empty();
		}
	}

	cout << ans << "\n";
	return 0;
}