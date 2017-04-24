#include <bits/stdc++.h>
using namespace std;

int main() {
	int k, a, b;
	cin >> k >> a >> b;

	int total = a / k + b / k;
	if(a % k == 0 && b % k == 0) {
		cout << total << "\n";
	} else if(a % k == 0) {
		if(a / k >= 1) {
			cout << total << "\n";
		} else {
			cout << "-1\n";
		}
	} else if(b % k == 0) {
		if(b / k >= 1) {
			cout << total << "\n";
		} else {
			cout << "-1\n";
		}
	} else {
		if(a/k >= 1 && b/k >= 1) {
			cout << total << "\n";
		} else {
			cout << "-1\n";
		}
	}
	return 0;
}