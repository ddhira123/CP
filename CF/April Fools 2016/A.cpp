#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	long long ans;
	if(n <= 12) ans = 1 << n;
	else {
		ans = 8092;
		for(int i = 13 ; i < n ; i++)
			ans *= 2;
	}
	cout << ans << endl;
	return 0;
}