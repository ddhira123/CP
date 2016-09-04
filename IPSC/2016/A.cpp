#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
	for(int tc = 0 ; tc < t ; tc++) {
		string s = "";
		for(int i = 0 ; i < 10 ; i++) {
			string x; cin >> x;
			s += x;
		}
		s += "AA";
		cout << s << endl;
		assert(s.length() == 42);
	}
	return 0;
}