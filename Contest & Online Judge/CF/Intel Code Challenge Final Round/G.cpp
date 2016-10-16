// completely wrong
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 2*N;
const long long MOD = 1e9 + 7;

int n, m;
int u[M], v[M];
long long c[M];
int vis[N][2];

vector<pair<int,int>> adj[N];

void make(int x) {
	for(int i = 1 ; i <= n ; i++) adj[i].clear();
	for(int i = 1 ; i <= m ; i++) {
		int cost;
		if((c[i] & (1ll << x)) > 0) {
			cost = 1;
		}
		else
			cost = 0;
		adj[u[i]].push_back({v[i],cost});
		adj[v[i]].push_back({u[i],cost});
		//printf("x %d add %d %d %d\n",x,u[i],v[i],cost);
	}
}

void reset() {
	for(int i = 1 ; i <= n ; i++)
		vis[i][0] = vis[i][1] = 0;
}

set<int> haha;

long long bfs(int x) {
	//printf("start %d\n",x);
	queue<pair<int,int>> q;
	q.push({x,0});
	vis[x][0] = 1;

	vector<int> seen;
	while(!q.empty()) {
		pair<int,int> now = q.front();
		q.pop();
		seen.push_back(now.first);

		for(pair<int,int> edge : adj[now.first]) {
			int nxt = edge.first;
			int co = now.second ^ edge.second;
			if(!vis[nxt][co]) {
				vis[nxt][co] = 1;
				q.push({nxt,co});
			}
		}
		//printf("masuk %d %d\n",now.first,now.second);
	}

	sort(seen.begin(),seen.end());
	seen.erase(unique(seen.begin(),seen.end()),seen.end());

	int satu = 0;
	int nol = 0;
	long long ret = 0;

	for(int i = 0 ; i < seen.size() ; i++) {
		assert(haha.find(seen[i]) == haha.end());
		haha.insert(seen[i]);

		int y = seen[i];
		if(vis[y][0] + vis[y][1] == 2)
			ret += i;
		else if(vis[y][0])
			ret += satu;
		else if(vis[y][1])
			ret += nol;
		satu += vis[y][1];
		nol += vis[y][0];
		ret %= MOD;
	}

	return ret;
}

void read() {
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= m ; i++) {
		scanf("%d %d %lld",u + i,v + i,c + i);
	}
}

long long solve() {
	long long ret = 0;
	for(int i = 0 ; i < 63 ; i++) {
		reset();
		make(i);
		long long ways = 0;
		haha.clear();
		for(int j = 1 ; j <= n ; j++)
			if(vis[j][0] + vis[j][1] == 0)
				ways = (ways + bfs(j)) % MOD;
		long long add = (1ll << i) % MOD;
		ret = (ret + ways * add) % MOD;
	}
	assert(ret >= 0 && ret < MOD);
	return ret;
}

int main() { 
	read();
	printf("%lld\n",solve());
	return 0;
} 