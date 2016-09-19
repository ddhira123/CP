#include <bits/stdc++.h>
using namespace std;

const int N = 50005;
const int TRY = 69;
const double EPS = 1e-9;
const double MAXX = 1e6;
const double INF = MAXX * N * 2.0;

struct edge {
	int to;
	double cost;
};

double dp[N];
bool vis[N];
vector<edge> adj[N];
int n,m;

double solve(int now) {
	if(now == n)
		return 0;

	double &ret = dp[now];
	if(vis[now]) return ret;

	vis[now] = 1;
	ret = -INF;

	for(edge x : adj[now]) {
		int to = x.to;
		double cost = x.cost;

		ret = max(ret,cost + solve(to));
	}

	return ret;
}

double DP(double val) {
	for(int i = 1 ; i <= n ; i++) {
		vis[i] = 0;
		for(edge &x : adj[i]) {
			x.cost -= val;
		}
	}

	double res = solve(1);

	for(int i = 1 ; i <= n ; i++) {
		vis[i] = 0;
		for(edge &x : adj[i]) {
			x.cost += val;
		}
	}

	return res;	
}

void read() {
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= m ; i++) {
		int from,to;
		double cost;

		scanf("%d %d %lf",&from,&to,&cost);
		adj[from].push_back((edge){to,cost});
	}
}

void solve() {
	double lo = 0.0;
	double hi = MAXX;

	for(int i = 0 ; i < TRY ; i++) {
		double mid = (lo + hi) / 2.0;

		if(DP(mid) > -EPS)
			lo = mid;
		else
			hi = mid;
	}

	printf("%.9lf\n",lo);
}

int main() {
	read();
	solve();
	return 0;
}