#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const int MAXN = 100005;

int ans[MAXN];
int n,m;

int low[MAXN], num[MAXN], vis[MAXN];
vector<int> stek, adj[MAXN];
int cnt;

void tarjan(int v) {
	low[v] = num[v] = cnt++;
	vis[v] = 1; // mark as inside stack
	stek.pb(v);
	
	for(int nex : adj[v]) {
		if(vis[nex] == 0) tarjan(nex);
		if(vis[nex] == 1) low[v] = min(low[v],low[nex]);
	}
	
	if(low[v] == num[v]) {
		int mins = n;
		vector<int> scc;
		while(1) {
			int u = stek.back(); stek.pop_back();
			mins = min(mins,u);
			vis[u] = 2; // mark as out of stack and has been processed
			scc.pb(u);
			if(u == v) break;
		}
		for(int u : scc)
			ans[u] = mins;
	}
}

int main() {
	scanf("%d %d",&n,&m);
	for(int i = 0 ; i < m ; i++) {
		int u,v;
		scanf("%d %d",&u,&v);
		adj[u].pb(v);
	}
	for(int i = 0 ; i < n ; i++) {
		if(num[i] == 0)
			tarjan(i);		
		printf("%d\n",ans[i]);	
	}		
	return 0;
}