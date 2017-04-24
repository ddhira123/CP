#include <bits/stdc++.h>
using namespace std;

// what the fuck am i doing
int get(string s) {
	int mins = 100000;
	for(int i = 1 ; i + 1 < s.length() ; i++)
		if(s[i] == '2') {
			int lol = 10 * (s[i] - '0') + s[i + 1] - '0';
			mins = min(mins,lol);
		}
	return mins;	
}

int main() {
	string s; cin >> s;
	cout << get(s) << endl;
	return 0;
}