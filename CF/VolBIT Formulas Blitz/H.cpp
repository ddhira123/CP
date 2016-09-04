#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	long long ans = 1;
	for(int i = n ; i > n - 5 ; i--)
		ans *= i;
	ans = (ans / 120) * ans;
	cout << ans << endl;
	return 0;
}