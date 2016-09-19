#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 5;
const long long INF = 1e12;

vector<pair<int,int>> adj[N];
int dist;
long long dp[N];
int n, m;

long long solve(int now,int len) {
	if(now == n) {
		dist = len;
		dp[now] = 0;
		return 0;
	}

	long long &ret = dp[now];
	if(ret != -1) return ret;

	ret = -INF;
	for(pair<int,int> nex : adj[now]) {
		long long way = solve(nex.first,len+1);
		way += nex.second;
		ret = max(ret,way);
	}

	return ret;
}

void read() {
	scanf("%d %d",&n,&m);
	for(int i = 0 ; i < m ; i++) {
		int u, v, c;
		scanf("%d %d %d",&u,&v,&c);
		adj[u].push_back({v,c});
	}
}

double DP() {
	memset(dp,-1,sizeof dp);
	long long ret = solve(1,0);
	return (double)ret / dist;
}

int main() {
	read();
	printf("%.9lf\n",DP());
	return 0;
}