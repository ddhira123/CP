#include <bits/stdc++.h>
using namespace std;

int hor, ver;
string s;

int main() {
	int n; cin >> n;
	cin >> s;
	int ans = 1;

	for(char x : s) {
		if(x == 'L' || x == 'R') {
			if(hor == 0) {
				hor = x;
			}
			else if(x != hor) {
				ver = 0;
				hor = x;
				ans++;
			}
		}
		else {
			if(ver == 0) {
				ver = x;
			}
			else if(x != ver) {
				ver = x;
				hor = 0;
				ans++;
			}
		}
	}

	cout << ans << "\n";
	return 0;
}