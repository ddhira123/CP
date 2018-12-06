/**
	LCA using sparse table
	
	We store each 2^k ancestor for each node
	so we can "jump" with length 2^k
	this code assumes that tree is rooted at 1
	
	Complexity : O(N log N) for building
				 O(log N) for query
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int LOG = 20;

int ancestor[N][LOG]; // "sparse table"
int depth[N];
vector<int> adj[N];
int n,q;

void buildSparseTable(int now,int prv) {
	depth[now] = depth[prv] + 1;
	ancestor[now][0] = prv;
	
	for(int i = 1 ; (1 << i) <= depth[now] ; i++) {
		int papa = ancestor[now][i - 1];
		int grandpa = ancestor[papa][i - 1];
		
		ancestor[now][i] = grandpa;
	}
}

void DFS(int now,int prv) {
	for(int nex : adj[now]) {
		if(nex == prv) continue;
		
		buildSparseTable(nex,now);
		DFS(nex,now);
	}
}

int getLCA(int u,int v) {
	if(depth[u] < depth[v]) swap(u,v);
	
	int diff = depth[u] - depth[v];
	
	// move u into the same level with v
	for(int i = 0 ; diff > 0 ; i++) {
		if(diff & (1 << i)) {
			u = ancestor[u][i];
			diff ^= (1 << i);
		}
	}
	
	// special case : if v is u's ancestor
	if(u == v) {
		return u;
	}
	
	// general case : "jump" until their parent is the same with 2^k trick
	int power = 0;
	
	while((1 << power) <= depth[u]) {
		power++;
	}
	
	power--;
	
	for(int i = power ; i >= 0 ; i--) {
		if((1 << i) <= depth[u] && ancestor[u][i] != ancestor[v][i]) {
			u = ancestor[u][i];
			v = ancestor[v][i];
		}
	}
	
	// now LCA is their parent
	return ancestor[u][0];
}

void readInput() {
	scanf("%d",&n);
	
	for(int i = 1 ; i < n ; i++) {
		int u,v;
		scanf("%d %d",&u,&v);
		
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

void solveQuery() {
	scanf("%d",&q);
	
	for(int i = 1 ; i <= q ; i++) {
		int u,v;
		
		scanf("%d %d",&u,&v);
		printf("LCA of %d and %d is %d\n",u,v,getLCA(u,v));
	}
}

int main() {
	readInput();
	DFS(1,0);
	solveQuery();
	return 0;
}
