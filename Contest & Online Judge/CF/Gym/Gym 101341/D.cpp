#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, x; cin >> n >> x;
	int fpb = 0;
	for(int i = 0 ; i < n ; i++) {
		int y; cin >> y;
		fpb = fpb == 0 ? y : __gcd(fpb, y);
	}

	if(abs(x) % fpb == 0) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}
	return 0;
}