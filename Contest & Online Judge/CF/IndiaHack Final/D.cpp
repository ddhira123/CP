#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;

#define fi first
#define se second
#define pb push_back

const int N = 55;

struct Dinic {
	struct Edge {
		int from;
		int to;
		int flow;
	};

	vector<Edge> elist;
	vector<int> adj[N];
	int saiz;

	int ptr[N];
	int dist[N];

	int source,sink;
	int num;

	Dinic(int _s = 0,int _t = 0,int _num = 0) {
		source = _s;
		sink = _t;
		num = _num;
		reset();
	}

	void reset() {
		for(int i = 0 ; i <= num ; i++)
			adj[i].clear();
		elist.clear();
		saiz = 0;
	}

	void add_edge(int from,int to,int flow) {
		adj[from].push_back(saiz++);
		adj[to].push_back(saiz++);

		elist.push_back((Edge){from,to,flow});
		elist.push_back((Edge){to,from,0});
	}

	bool BFS() {
		for(int i = 0 ; i <= num ; i++)
			dist[i] = -1;
		queue<int> q;
		q.push(source);
		dist[source] = 0;

		while(!q.empty() && dist[sink] == -1) {
			int now = q.front();
			q.pop();
			for(int idx : adj[now]) {
				int to = elist[idx].to;
				int flow = elist[idx].flow;

				if(dist[to] == -1 && flow > 0) {
					dist[to] = dist[now] + 1;
					q.push(to);
				}
			}
		}

		return dist[sink] != -1;
	}

	int augment(int now,int f) {
		if(now == sink)
			return f;

		for(int &i = ptr[now] ; i < adj[now].size() ; i++) {
			int idx = adj[now][i];
			int to = elist[idx].to;
			int flow = elist[idx].flow;

			if(dist[to] == dist[now] + 1 && flow > 0) {
				int res = augment(to,min(f,flow));
				if(res > 0) {
					elist[idx].flow -= res;
					elist[idx ^ 1].flow += res;
					return res;
				}
			}
		}

		return 0;
	}

	int maxFlow() {
		int mf = 0;
		while(BFS()) {
			for(int i = 0 ; i <= num ; i++)
				ptr[i] = 0;
			int add = augment(source,(int)1e9);
			while(add > 0) {
				mf += add;
				add = augment(source,(int)1e9);
			}
		}
		return mf;
	} 
};

Dinic network;
int u[505], v[505], w[505];
int n,m,x;

void read() {
	scanf("%d %d %d",&n,&m,&x);
	for(int i = 0 ; i < m ; i++) {
		scanf("%d %d %d",u + i,v + i,w + i);
	}
}

void build(int s,int t,double ww) {
	network = Dinic(s,t,t);

	network.add_edge(s,1,x);
	network.add_edge(n,t,x);

	for(int i = 0 ; i < m ; i++) {
		int uu = u[i];
		int vv = v[i];
		double maks = w[i] / ww;
		maks = min(maks,(double)x);
		maks = floor(maks + 1e-9);
		//printf("ww %.12lf maks %d\n",ww,(int)maks);
		network.add_edge(uu,vv,(int)maks);
	}
}

void solve() {
	int source = 0;
	int sink = n + 1;

	double lo = 0,hi = 1e6;

	for(int i = 0 ; i < 200 ; i++) {
		double mid = (lo + hi) / 2.0;
		build(source,sink,mid);

		int mf = network.maxFlow();
		if(mf == x)
			lo = mid;
		else
			hi = mid;
	}

	printf("%.12lf\n",lo * x);
}

int main() {
	read();
	solve();
	return 0;
}