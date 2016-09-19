#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int M = 2005;
const double EPS = 1e-9;
const long long MAXX = 1e6;
const long long INF = MAXX * N * 2;

struct edge {
	int to;
	int cost;
};

long long dp[N][M];
bool vis[N];
vector<edge> adj[N];
int n,m;
pair<long long,int> haha[N];

long long solve(int now,int sisa) {
	if(sisa < 0) return -INF;

	if(now == n) {
		if(sisa == 0) return 0;
		return -INF;
	}

	long long &ret = dp[now][sisa];
	if(ret > -INF) return ret;

	ret = -INF + 1;

	for(edge x : adj[now]) {
		int to = x.to;
		int cost = x.cost;
		long long lala = solve(to,sisa - 1);
		if(lala < 0ll) continue;
		ret = max(ret,cost + solve(to,sisa - 1));
	}

	return ret;
}

void read() {
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= m ; i++) {
		int from,to;
		int cost;

		scanf("%d %d %d",&from,&to,&cost);
		adj[from].push_back((edge){to,cost});
	}
}

void solve() {
	for(int i = 1 ; i <= n ; i++)
		for(int j = 0 ; j < M ; j++)
			dp[i][j] = -INF;
	double ans = 0;
	
	for(int i = 1 ; i < M; i++) {
		long long ret = solve(1,i);
		if(ret > 0) ans = max(ans,(double)ret / i);
	}	

	printf("%.9lf\n",ans);
}

int main() {
	read();
	solve();
	return 0;
}