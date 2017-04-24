#include <bits/stdc++.h>
using namespace std;

int a;
string s;

int main() {
	cin >> a;
	cin >> s;
	int ans = 0;
	if(s[3] > '5') s[3] = '5';
	if(a == 12) {
		if(s[1] == '0')
			s[0] = '1';
		else if(s[1] <= '2') {
			if(s[0] > '1') s[0] = '1';
		}
		else {
			if(s[0] > '0') s[0] = '0';
		}
	}
	else {
		if(s[1] <= '3') {
			if(s[0] > '2') s[0] = '2';
		}
		else  {
			if(s[0] > '1') s[0] = '1';
		}
	}
	cout << s << "\n";
	return 0;
}