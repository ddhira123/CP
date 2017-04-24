#include <bits/stdc++.h>
using namespace std;

int n, cur;

void fail() {
	cout << "NO\n";
	exit(0);
}

int main() {
	cin >> n;
	cur = 0;

	for(int i = 0 ; i < n ; i++) {
		string dir;
		int x;
		cin >> x >> dir;

		if(cur == 0 && dir != "South") {
			fail();
		}
		if(cur == -20000 && dir != "North") {
			fail();
		}
		if(dir == "North") {
			if(fabs(cur) < x) {
				fail();
			}
			cur += x;
		}
		else if(dir == "South") {
			if(20000 - fabs(cur) < x) {
				fail();
			}
			cur -= x;
		}
	}
	if(cur != 0) {
		fail();
	}
	cout << "YES\n";
	return 0;
}