#include <bits/stdc++.h>
using namespace std;

bool ada[256];

int main() {
	string s; cin >> s;
	char maks = 'a';
	for(char x : s) {
		ada[x] = 1;
		maks = max(maks, x);
	}

	for(int i = 'a' ; i <= maks ; i++)
		if(!ada[i]) {
			cout << "NO\n";
			return 0;
		}

	if(s[0] != 'a') {
		cout << "NO\n";
		return 0;
	}

	for(int i = 0 ; i < s.length() ; i++) {
		if(ada[s[i]]) {
			ada[s[i]] = 0;
			if(s[i] == 'a') continue;

			bool ok = 0;
			for(int j = 0 ; j < i ; j++)
				ok |= (s[j]+1 == s[i]);

			if(!ok) {
				cout << "NO\n";
				return 0;
			}
		}
	}

	cout << "YES\n";	
	return 0;
}