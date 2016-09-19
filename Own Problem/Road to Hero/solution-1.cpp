#include <bits/stdc++.h>
using namespace std;

const int N = 15;

struct edge {
	int to;
	double cost;
};

double dp[N];
bool vis[N];
vector<edge> adj[N];
int n,m;

double ans = 0.0;

void rec(int now,double jum,int path) {
	if(now == n){
		ans = max(ans,jum / path);
		return;
	}

	double ret = 0.0;

	for(edge x : adj[now]) {
		int to = x.to;
		double cost = x.cost;

		rec(to,jum + cost,path + 1);
	}
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
	rec(1,0,0);
	printf("%.9lf\n",ans);
}

int main() {
	read();
	solve();
	return 0;
}