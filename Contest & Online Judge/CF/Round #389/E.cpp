#include <bits/stdc++.h>
using namespace std;

const int MX = 1e7;
const long long MAGIC = 4e18;

int n, k;
long long dp[MX+5];

int main() {
	scanf("%d %d",&n,&k);
	for(int i = 0 ; i < n ; i++) {
		int x; scanf("%d",&x);
		dp[x]++;
	}

	long long tot = 0;
	for(int i = MX ; i >= 1 ; i--) {
		tot += dp[i];
		//if(i <= 10) printf("%d %lld %lld\n",i,tot,dp[i]);
		if(i*2 <= MX) {
			tot -= dp[2*i];
			if(i > 1)
				tot -= dp[2*i-1];
		}

		//if(i <= 10) printf("%d %lld %lld\n",i,tot,dp[i]);

		if(tot >= k) {
			printf("%d\n",i);
			return 0;
		}

		dp[i/2] = min(1ll * MAGIC, 1ll * dp[i/2] + dp[i]);
		dp[(i+1)/2] = min(1ll * MAGIC, 1ll * dp[(i+1)/2] + dp[i]);
	}

	printf("-1\n");
	return 0;
}