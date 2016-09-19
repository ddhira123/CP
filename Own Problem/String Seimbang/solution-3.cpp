#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	int n;
	string s;
	cin >> n;
	cin >> s;

	int i = 1;
	while(i < s.length() && s[i]==s[i-1]) i++;

	int ans = min(i,n-i);
	if(s[0] == ')') ans = 0;
	cout << ans << "\n";
	return 0;
}