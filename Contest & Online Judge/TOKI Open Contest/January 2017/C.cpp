#include <bits/stdc++.h>
using namespace std;

const int N = 505;

long long dp[N][N][2];
int cnt[N];
int n, k;
long long cost[N];
long long val[N];
int arr[N];
long long penalty;

long long solve(int l,int r,int opt) {
	if(l > r) return 0;
	long long &ret = dp[l][r][opt];
	if(ret != -1) return ret;

	ret = 0;
	if(opt == 0) {
		ret = max(solve(l+1,r,1) + val[l], solve(l,r-1,1) + val[r]);
	} else {
		ret = min(solve(l+1,r,0), solve(l,r-1,0));
	}

	return ret;
}

void read() {
	scanf("%d %d",&n,&k);
	for(int i = 1 ; i <= k ; i++)
		scanf("%lld", cost + i);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",arr + i);
}

void prepare() {
	memset(dp, -1, sizeof dp);
	for(int i = 1 ; i <= n ; i++)
		cnt[arr[i]]++;
	for(int i = 1 ; i <= k ; i++)
		penalty += cost[i] * cnt[i] * cnt[i];
	for(int i = 1 ; i <= n ; i++)
		val[i] = cost[arr[i]] * 2 * cnt[arr[i]];
}

int main() {
	read();
	prepare();
	printf("%lld\n", solve(1,n,0) - penalty);
	return 0;
}