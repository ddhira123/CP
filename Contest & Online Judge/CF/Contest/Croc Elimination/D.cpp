#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;

#define fi first
#define se second
#define pb push_back

int deg[100005];
int u[100005];
int v[100005];

vector<int> adj[100005];
int n,m;

bool valid() {
	queue<int> q;
	for(int i = 1 ; i <= n ; i++)
		if(deg[i] == 0) {
			q.push(i);
			//printf("add %d\n",i);
		}

	for(int i = 1 ; i <= n ; i++) {
		if(q.size() != 1) return 0;
		int now = q.front();
		q.pop();

		for(int nex : adj[now]) {
			deg[nex]--;
			if(deg[nex] == 0) {
				q.push(nex);
				//printf("add %d\n",nex);
			}
		}
	}

	return 1;	
}

void build(int x) {
	for(int i = 1 ; i <= x ; i++) {
		deg[v[i]]++;
		adj[u[i]].pb(v[i]);
	}
}

void reset() {
	for(int i = 1 ; i <= n ; i++) {
		adj[i].clear();
		deg[i] = 0;
	}
}

int main() {
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= m ; i++) {
		scanf("%d %d",u + i,v + i);
	}

	int lo = 0,hi = m + 1;
	while(lo < hi) {
		int mid = (lo + hi) / 2;
		reset();
		build(mid);
		//printf("%d\n",mid);
		if(valid())
			hi = mid;
		else
			lo = mid + 1;
	}

	if(lo > m) lo = -1;
	printf("%d\n",lo);
	return 0;
}