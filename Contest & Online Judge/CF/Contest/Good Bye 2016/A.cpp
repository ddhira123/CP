#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, k;
	cin >> n >> k;
	int sisa = 240 - k;
	int ans = 0;

	for(int i = 1 ; i <= n ; i++) {
		if(5*i > sisa) continue;
		ans = i;
		sisa -= 5 * i;
	}

	cout << ans << "\n";
	return 0;
}