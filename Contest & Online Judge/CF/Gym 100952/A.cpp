#include <bits/stdc++.h>
using namespace std;

void solve() {
	int a[3], b[3];
	for(int i = 0 ; i < 3 ; i++) cin >> a[i];
	for(int i = 0 ; i < 3 ; i++) cin >> b[i];
	for(int i = 0 ; i < 3 ; i++) {
		if(a[i] < b[i]) {
			cout << "Player1\n";
			return;
		}
		if(a[i] > b[i]) {
			cout << "Player2\n";
			return;
		}
	}
	cout << "Tie\n";
}

int main() {
	int t; cin >> t;
	for(int i = 0 ; i < t ; i++) solve();
	return 0;
}