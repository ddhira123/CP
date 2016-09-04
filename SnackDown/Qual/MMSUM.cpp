#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 1e5 + 5;
const LL INF = (LL)4e18;

LL dp[N][2];
LL arr[N];
int n;

LL solve(int pos,int can) {
	if(pos > n) return 0;
	LL &ret = dp[pos][can];
	if(ret > -INF) return ret;

	ret = 0;
	ret = max(ret,arr[pos] + solve(pos+1,can));
	if(can) ret = max(ret,solve(pos+1,0));

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		cin >> n;
		for(int i = 1 ; i <= n ; i++) {
			cin >> arr[i];
			dp[i][0] = dp[i][1] = -INF;
		}

		LL ans = -INF;
		for(int i = 1 ; i <= n ; i++)
			ans = max(ans,arr[i] + solve(i+1,1));

		cout << ans << endl;
	}
	return 0;
}