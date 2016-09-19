#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	long long n;
	string s;
	cin >> n;
	cin >> s;

	if(s[0] == ')') n--;
	if(s[s.length()-1] == '(') n--;
	n /= 2;

	cout << n*(n+1)/2 << "\n";
	return 0;
}