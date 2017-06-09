#include <bits/stdc++.h>
using namespace std;

string s;
int n;
int underscore;
string dummy;

void rec(int pos) {
	if(pos == underscore) {
		n--;
		if(n == 0) {
			int it = 0;

			for(char ch : s) {
				if(ch == '_') {
					cout << dummy[it++];
				} else {
					cout << ch;
				}
			}
			cout << endl;

			exit(0);
		}
	} else {
		for(char i = 'a' ; i <= 'z' ; i++) {
			dummy[pos] = i;
			rec(pos+1);
		}
	}
}

int main() {
	cin >> s >> n;
	for(char x : s)
		if(x == '_')
			underscore++;

	if(underscore == 0) {
		cout << s << endl;
	} else {
		dummy = string(underscore, 'a');
		rec(0);
	}

	return 0;
}