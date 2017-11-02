#include <bits/stdc++.h>
using namespace std;

string s;

bool check(int a) {
	for(int i = a, j = s.length()-1 ; i < s.length() ; i++, j--) {
		if(s[i] != s[j]) {
			return false;
		}
	}
	return true;
}

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		cin >> s;
		int ret = -1;
		for(int i = s.length()-1 ; i >= 0 ; i--)
			if(check(i))
				ret = i;

		printf("Kasus #%d: ", tc);
		cout << s;
		for(int i = ret-1 ; i >= 0 ; i--)
			cout << s[i];
		cout << endl;
	}
	return 0;
}