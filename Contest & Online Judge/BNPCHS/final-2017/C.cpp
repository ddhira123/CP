#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;

int dp[N][N];
int t[N], k[N], x[N];
int n;

int solve(int pos, int day) {
	if(pos == n) return 0;

	int &ret = dp[pos][day];
	if(ret != -1) return ret;

	ret = solve(pos+1, day);
	if(k[pos] >= day) {
		ret = max(ret, solve(pos+1, min(N-1, day + x[pos])) + t[pos]);
	}

	// printf("pos %d day %d ret %d\n", pos, day, ret);

	return ret;
}

int main() {
	int tc ; cin >> tc;
	for(int tes = 1 ; tes <= tc ; tes++) {

		cin >> n;
		for(int i = 0 ; i < n ; i++) {
			cin >> t[i] >> k[i] >> x[i];
			// printf("%d -> %d %d %d\n", i, t[i], k[i], x[i]);
		}

		memset(dp, -1, sizeof dp);
		printf("Kasus #%d: %d\n", tes, solve(0, 1));
	}
	return 0;
}