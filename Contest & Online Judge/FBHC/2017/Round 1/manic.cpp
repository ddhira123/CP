#include <bits/stdc++.h>
using namespace std;

const int N = 103;
const int M = 5003;
const int K = 5003;
const int INF = 1011222333;

int dp[K][N][2][2];
int u[M], v[M], w[M];
int s[K], d[K];
int dist[N][N];
int n, m, k;

int solve(int idx,int city,int after,int now) {
	if(idx == k+1)
		return 0;

	int &ret = dp[idx][city][after][now];
	if(ret != -1)
		return ret;

	ret = INF;
	if(now == 0)
		ret = min(ret, solve(idx, s[idx], after, 1) + dist[city][s[idx]]);
	if(now == 1) {
		if(after == 0 && idx+1 <= k)
			ret = min(ret, solve(idx, s[idx+1], 1, now) + dist[city][s[idx+1]]);
		ret = min(ret, solve(idx+1, d[idx], 0, after) + dist[city][d[idx]]);
	}

	//printf("%d %d %d %d -> %d\n", idx, city, after, now, ret);
	return ret;
}

int calc() {
	memset(dp, -1, sizeof dp);
	int ret = solve(1, 1, 0, 0);
	if(ret >= INF)
		ret = -1;
	return ret;
}

void warshall() {
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n ; j++)
			dist[i][j] = i == j ? 0 : INF;

	for(int i = 1 ; i <= m ; i++) {
		int uu = u[i];
		int vv = v[i];
		dist[uu][vv] = dist[vv][uu] = min(dist[vv][uu], w[i]);
	}

	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n ; j++)
			for(int ii = 1 ; ii <= n ; ii++)
				dist[j][ii] = min(dist[j][ii], dist[j][i] + dist[i][ii]);
}

void read() {
	scanf("%d %d %d",&n,&m,&k);
	for(int i = 1 ; i <= m ; i++)
		scanf("%d %d %d",u + i,v + i,w + i);
	for(int i = 1 ; i <= k ; i++)
		scanf("%d %d",s + i,d + i);
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		warshall();
		printf("Case #%d: %d\n",tc, calc());
		cerr << tc << "\n";
	}
	return 0;
}