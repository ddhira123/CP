#include <bits/stdc++.h>
using namespace std;

int solve(int n,int m) {
	int ret = 0;
	int udah = 1;
	n++;
	while(udah < n && udah < m) {
		ret++;
		udah *= 2;
	}
	if(udah >= n) return ret;
	ret += (n-udah+m-1) / m;
	return ret;
}

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		int n, m;
		cin >> n >> m;
		cout << solve(n,m) << "\n";
	}
	return 0;
}