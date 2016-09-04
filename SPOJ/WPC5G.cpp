#include <bits/stdc++.h>
using namespace std;

#define pb push_back

const int N = 505;
const int INF = (int)1e9;

struct edge {
	int from;
	int to;
	int cap;
};

vector<edge> edgeList;
vector<int> adj[N];
int saiz;
int dist[N];
int ptr[N];

char tipe[N][3];
vector<int> love[N], hate[N];
int n;
int n1,n2;

// man i love max flow
// just kidding
// start of maxFlow routines

void addEdge(int from,int to,int cap) {
	adj[from].pb(saiz++);
	adj[to].pb(saiz++);

	edgeList.pb((edge){from,to,cap});
	edgeList.pb((edge){to,from,0});
}

bool BFS() {
	for(int i = 0 ; i <= n + 1 ; i++) {
		dist[i] = -1;
	}

	queue<int> q;

	dist[0] = 0;
	q.push(0);

	while(!q.empty()) {
		int now = q.front();
		q.pop();

		for(int idx : adj[now]) {
			int to = edgeList[idx].to;
			int cap = edgeList[idx].cap;

			if(dist[to] == -1 && cap > 0) {
				dist[to] = dist[now] + 1;
				q.push(to);
			}
		}
	}

	return dist[n + 1] != -1;
}

int augment(int now,int flow) {
	if(now == n + 1) {
		return flow;
	}

	for(int &i = ptr[now] ; i < adj[now].size() ; i++) {
		int idx = adj[now][i];
		int to = edgeList[idx].to;
		int cap = edgeList[idx].cap;

		if(dist[to] != dist[now] + 1 || cap == 0) continue;

		int ret = augment(to,min(flow,cap));
		if(ret > 0) {
			edgeList[idx].cap -= ret;
			edgeList[idx ^ 1].cap += ret;

			return ret;
		}
	}

	return 0;
}

int maxFlow() {
	int ret = 0;

	while(BFS()) {
		for(int i = 0 ; i <= n + 1 ; i++)
			ptr[i] = 0;

		int add = augment(0,INF);
		while(add > 0) {
			ret += add;
			add = augment(0,INF);
		}
	}

	return ret;
}

int MIS() {
	return n - maxFlow();
}

// end of maxFlow routines

// start of solver

bool containSame(vector<int> &a, vector<int> &b) {
	bool ok = 1;
	int iter = 0;

	for(int x : a) {
		while(iter < b.size() && b[iter] < x) iter++;

		if(iter < b.size() && b[iter] == x) {
			ok = 0;
			break;
		}
	}

	return !ok;
}

void read() {
	scanf("%d %d",&n1,&n2);
	scanf("%d",&n);

	for(int i = 1 ; i <= n ; i++) {
		scanf("%s",tipe[i]);
		int temp;

		while(scanf("%d",&temp) == 1 && temp != -1) {
			love[i].pb(temp);
		}

		while(scanf("%d",&temp) == 1 && temp != -1) {
			hate[i].pb(temp);
		}

		sort(love[i].begin(),love[i].end());
		sort(hate[i].begin(),hate[i].end());

		//printf("finished reading %d\n",i);
	}
}

void buildGraph() {
	for(int i = 1 ; i <= n ; i++)
		if(tipe[i][0] == 'B') {
			addEdge(i,n + 1,1);
		}
		else {
			addEdge(0,i,1);

			for(int j = 0 ; j <= n ; j++)
				if(tipe[j][0] == 'B') {
					bool enemy = containSame(love[i],hate[j]) || containSame(love[j],hate[i]);

					if(enemy) {
						addEdge(i,j,1);
					}
				}
		}
}

void solve() {
	buildGraph();
	printf("%d\n",MIS());
}

// end of solver

int main() {
	read();
	solve();
	return 0;
}