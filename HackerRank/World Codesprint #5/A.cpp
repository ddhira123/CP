#include <bits/stdc++.h>
using namespace std;

int main() {
	string s; cin >> s;
	int ans = 1;
	for(char x : s) {
		if('A' <= x && x <= 'Z')
			ans++;
	}
	cout << ans << endl;
	return 0;
}