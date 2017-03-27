#include <bits/stdc++.h>
using namespace std;

struct edge {
	int from;
	int to;
	int cap;
	int initCap;
};

struct treeEdge {
	int from;
	int to;
	int val;
	
	bool operator <(treeEdge other) const {
		return val < other.val;
	}
};

typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back

const int N = 155;
const int Q = 35;
const int INF = (int)1e9;

// for max flow
vector<edge> edgeList;
vector<int> adj[N];
int saiz;

// for augmenting
int dist[N];
int ptr[N];

// storing gomory hu
vector<treeEdge> gomoryHu;
int parent[N];

// for disjoint set
int pset[N];
int member[N];

// for answering query
int ans[Q];
pii query[Q];
int numOfPair;

int n,m,q;

void reset() {
	edgeList.clear();
	gomoryHu.clear();
	saiz = 0;
	numOfPair = 0;
	
	for(int i = 1 ; i <= n ; i++) {
		adj[i].clear();
		
		pset[i] = i;
		member[i] = 1;
		parent[i] = 1;
	}
}

void addEdge(int from,int to,int cap) {
	edgeList.pb((edge){from,to,0,cap});
	edgeList.pb((edge){to,from,0,cap});
	
	adj[from].pb(saiz++);
	adj[to].pb(saiz++);
}

bool BFS(int source,int sink) {
	for(int i = 1 ; i <= n ; i++)
		dist[i] = -1;
	
	queue<int> q;
	dist[source] = 0;
	q.push(source);
	
	while(!q.empty()) {
		int now = q.front();
		
		q.pop();
		
		for(int nex : adj[now]) {
			int to = edgeList[nex].to;
			int cap = edgeList[nex].cap;
			
			if(dist[to] == -1 && cap > 0) {
				dist[to] = dist[now] + 1;
				q.push(to);
			}
		}
	}
	
	return dist[sink] != -1;	
}

int augment(int now,int sink,int minVal) {
	if(now == sink) {
		return minVal;
	}
	
	for(int &i = ptr[now] ; i < adj[now].size() ; i++) {
		int idx = adj[now][i];
		int to = edgeList[idx].to;
		int cap = edgeList[idx].cap;
		
		if(cap > 0 && dist[to] == dist[now] + 1) {
			int res = augment(to,sink,min(minVal,cap));
			
			if(res > 0) {
				edgeList[idx].cap -= res;
				edgeList[idx ^ 1].cap += res;
				return res;
			}
		}
	}
	
	return 0;
}

int maxFlow(int source,int sink) {
	for(edge &e : edgeList) {
		e.cap = e.initCap;
	}
	
	int mf = 0;
	
	while(BFS(source,sink)) {
		for(int i = 1 ; i <= n ; i++) {
			ptr[i] = 0;
		}
		
		int res = augment(source,sink,INF);
		
		while(res) {
			mf += res;
			res = augment(source,sink,INF);
		}
	}
	
	return mf;
}

void buildGomoryHu() {
	for(int i = 2 ; i <= n ; i++) {
		gomoryHu.pb((treeEdge){i,parent[i],maxFlow(i,parent[i])});
		
		for(int j = i + 1 ; j <= n ; j++) {
			if(dist[j] != -1 && parent[j] == parent[i]) {
				parent[j] = i;
			}
		}
	}
}

int finds(int x) {
	return x == pset[x] ? x : pset[x] = finds(pset[x]);
}

void join(int x,int y) {
	x = finds(x);
	y = finds(y);
	
	assert(x != y);
	
	numOfPair += member[y] * member[x];
	member[y] += member[x];
	pset[x] = y;
}

void readInput() {
	scanf("%d %d",&n,&m);
	
	reset();
	
	for(int i = 0 ; i < m ; i++) {
		int u,v,c;
		scanf("%d %d %d",&u,&v,&c);
		addEdge(u,v,c);
	}
	
	scanf("%d",&q);
	
	for(int i = 0 ; i < q ; i++) {
		scanf("%d",&query[i].fi);
		query[i].se = i;
	}
}

void solveQuery() {
	buildGomoryHu();
	
	sort(gomoryHu.begin(),gomoryHu.end());
	sort(query,query + q);
	
	int iter = q - 1;
	for(int i = n - 2 ; i >= 0 ; i--) {
		while(iter >= 0 && query[iter].fi >= gomoryHu[i].val) {
			ans[query[iter].se] = (n * (n - 1)) / 2 - numOfPair;
			iter--;
		}
		
		join(gomoryHu[i].from,gomoryHu[i].to);
	}
	
	while(iter >= 0) {
		ans[query[iter].se] = 0;
		iter--;
	}
	
	for(int i = 0 ; i < q ; i++) {
		printf("%d\n",ans[i]);
	}
}

int main() {
	int tc;
	scanf("%d",&tc);
	
	for(int t = 1 ; t <= tc ; t++) {
		if(t > 1) puts("");
		readInput();
		solveQuery();
	}
	return 0;
}