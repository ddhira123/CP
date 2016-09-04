#include <bits/stdc++.h>
using namespace std;

const int N = 205;
const int K = 55;
const int MOD = 1e9 + 7;

int dp[N][N][K];
int arr[N];
int n, m, k, d;

void read() {
	scanf("%d %d %d %d",&n,&m,&k,&d);
	for(int i = 0 ; i < n ; i++) {
		scanf("%d",arr + i);
	}
}

int solve(int pos,int sisa,int kk) {
	if(pos == n) {
		return sisa == 0 && kk == 0;
	}
	int &ret = dp[pos][sisa][kk];
	if(ret != -1) return ret;
	ret = solve(pos+1,sisa,kk);
	if(sisa) {
		if(arr[pos] >= d)
			ret += solve(pos+1,sisa-1,max(0,kk-1));
		else
			ret += solve(pos+1,sisa-1,kk);
	}
	ret %= MOD;
	return ret;
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		memset(dp,-1,sizeof dp);
		printf("%d\n",solve(0,m,k));
	}
	return 0;
}