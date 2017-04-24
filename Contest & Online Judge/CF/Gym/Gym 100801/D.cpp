#include <bits/stdc++.h>
using namespace std;

void OPEN(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

void CLOSE() {
	fclose(stdin);
	fclose(stdout);
}

typedef long long LL;

const LL MX = 1e18;

vector<LL> ans;

void solve(LL sisa, LL mul) {
	if(sisa == 0) return;
	while(sisa % 2 == 0) {
		sisa /= 2;
		mul *= 2;
	}
	LL x = 1;
	while(x*3 <= sisa) x *= 3;
	ans.push_back(mul * x);
	solve(sisa - x, mul);
}

int main() {
	OPEN("distribution");
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		LL n; cin >> n;

		ans.clear();
		solve(n, 1);

		cout << ans.size() << "\n";
		for(LL x : ans)
			cout << x << " ";
		cout << "\n";
	}
	CLOSE();
	return 0;
}