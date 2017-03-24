#include <bits/stdc++.h>
using namespace std;

int n;
string s;

int main() {
	cin >> n >> s;

	int satu = -1;
	int tot = 0;

	for(int i = 0 ; i < s.length() ; i++) {
		if(s[i] == '1') {
			satu = i;
		} else if(s[i] != '0'){
			tot++;
		}
	}

	if(tot == n) {
		cout << "-1\n";
		return 0;
	}

	for(int i = 0 ; i < s.length() ; i++) {
		if(s[i] == '1') {
			break;
		} else if(s[i] == '0') {
			tot++;
		}
	}

	if(tot == n) tot--;
	cout << tot << endl;
	return 0;
}