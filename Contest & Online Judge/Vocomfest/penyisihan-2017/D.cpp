#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int dp[N][N];
vector<pair<int,int>> v[N];

int solve(int a, int b) {
	if(b < 0) return -N;
	if(a == N) return 0;
	int &ret = dp[a][b];
	if(ret != -1) return ret;

	ret = solve(a+1, b);
	for(pair<int,int> x : v[a])
		ret = max(ret, 1 + solve(x.first+1, b - x.second));

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	int t; cin >> t;

	for(int tc = 1 ; tc <= t ; tc++) {

		for(int i = 0 ; i < N ; i++)
			v[i].clear();

		int n, m; cin >> n >> m;
		for(int i = 0 ; i < n ; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			v[a].push_back({b, c});
		}

		memset(dp, -1, sizeof dp);
		int ret = solve(0, m);

		cout << "Case #" << tc << ": " << ret << "\n";
	}
	return 0;
}