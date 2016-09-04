#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		int n; cin >> n;
		if(n != 1) cout << "Alice\n";
		else cout << "Bob\n";
	}
	return 0;
}