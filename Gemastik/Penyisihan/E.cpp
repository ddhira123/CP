#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int INF = 1e9;

int dp[N][N][2];
int k[N], v[N];
int n, s, p;

int solve(int pos,int sisa,int terbang) {
	if(sisa < 0) return -INF;
	if(pos == n) return 0;

	int &ret = dp[pos][sisa][terbang];
	if(ret != -1) return ret;

	ret = -INF;
	ret = max(ret,solve(pos+1,sisa - k[pos],0) + v[pos]);
	if(terbang) ret = max(ret,solve(pos+1,sisa,1));
	else		ret = max(ret,solve(pos+1,sisa-p,1));

	//printf("%d %d %d %d\n",pos,sisa,terbang,ret);
	return ret;
}

void read() {
	scanf("%d %d %d",&n,&s,&p);
	for(int i = 1 ; i < n ; i++) {
		scanf("%d %d",k + i,v + i);
		//printf("%d -> %d %d\n",i,k[i],v[i]);
	}
}

int DP() {
	memset(dp,-1,sizeof dp);
	int ret = -1;
	ret = max(ret,solve(1,s,0));
	return ret;
}

int main() {
	int t; scanf("%d",&t);

	for(int tc = 1; tc <= t ; tc++) {
		read();
		printf("%d\n",DP());
	}
	return 0;
}