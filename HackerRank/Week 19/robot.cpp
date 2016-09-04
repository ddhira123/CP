#include <bits/stdc++.h>
using namespace std;

int n,m,t;
int dari[1005], ke[1005];
int dp[1005][1005];

int solve(int now,int lama) {
	if(now > n) return 0;
	int &ret = dp[now][lama];
	if(ret != -1) return ret;
	int bef = ke[now - 1];
	ret = (int)2e9;

	ret = min(ret,solve(now + 1,lama) + abs(bef - dari[now]) + abs(dari[now] - ke[now]));
	ret = min(ret,solve(now + 1,bef) + abs(lama - dari[now]) + abs(dari[now] - ke[now]));

	return ret;
}

int main() {
	scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		scanf("%d %d",&m,&n);

		for(int i = 1 ; i <= n ; i++) {
			scanf("%d %d",dari + i,ke + i);
		}
		ke[0] = dari[1];

		memset(dp,-1,sizeof dp);
		int ans = (int)2e9;
		for(int i = 1 ; i <= m ; i++) {
			ans = min(ans,solve(1,i));
		}

		printf("%d\n",ans);
	}
	return 0;
}