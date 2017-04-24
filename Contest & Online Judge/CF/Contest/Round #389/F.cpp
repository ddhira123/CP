#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

bool mark[N];
int size[N];
int heavy[N];
vector<int> adj[N];
int n, k;
vector<int> lst[N];
priority_queue<pair<int,int>> pq;

void dfs(int now,int prv) {
	size[now] = mark[now];
	for(int nex : adj[now]) {
		if(nex == prv) continue;
		dfs(nex,now);
		size[now] += size[nex];
		heavy[now] = max(heavy[now], size[nex]);
	}
	heavy[now] = max(heavy[now], 2*k - size[now] + mark[now]);
}

int centroid() {
	dfs(1,-1);
	int root = 1;
	for(int i = 1 ; i <= n ; i++)
		if(heavy[i] < heavy[root])
			root = i;
	return root;	
}

void fetch(int now,int prv,int cnt) {
	if(mark[now]) 
		lst[cnt].push_back(now);

	for(int nex : adj[now]) {
		if(nex == prv) continue;
		fetch(nex,now,cnt);
	}
}

void solve() {
	int root = centroid();
	printf("1\n%d\n",root);

	int cnt = 0;
	for(int nex : adj[root]) {
		fetch(nex,root,cnt);
		cnt++;
	}

	if(mark[root]) {
		lst[cnt++].push_back(root);
	}

	for(int i = 0 ; i < cnt ; i++) {
		if(!lst[i].empty())
			pq.push({lst[i].size(),i});
	}

	while(!pq.empty()) {
		pair<int,int> a = pq.top();
		pq.pop();

		pair<int,int> b = pq.top();
		pq.pop();

		printf("%d %d %d\n",lst[a.second].back(), lst[b.second].back(), root);

		a.first--;
		b.first--;
		lst[a.second].pop_back();
		lst[b.second].pop_back();

		if(a.first)
			pq.push(a);
		if(b.first)
			pq.push(b);
	}
}

void read() {
	scanf("%d %d",&n,&k);
	for(int i = 1 ; i < n ; i++) {
		int u, v;
		scanf("%d %d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i = 1 ; i <= 2*k ; i++) {
		int x; scanf("%d",&x);
		mark[x] = 1;
	}
}

int main() {
	read();
	solve();
	return 0;
}