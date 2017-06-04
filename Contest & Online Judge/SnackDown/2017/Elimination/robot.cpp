#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int N2 = 105*105;

struct Dinic {
	struct Edge {
		int from;
		int to;
		int flow;
	};

	vector<Edge> elist;
	vector<int> adj[N2];
	int saiz;

	int ptr[N2];
	int dist[N2];

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
		// printf("%d -> %d f %d\n", from, to, flow);
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

	int maxFlow(int k) {
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

int n, m, k;
vector<int> adj[N];
int topo[N];
Dinic network;

void read() {
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 0 ; i < m ; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--; v--;

		adj[u].push_back(v);
	}
}

int solve() {
	if(k > n) return -1;

	int source = 0;
	int sink = n*n;

	network = Dinic(source, sink, sink);

	for(int i = 0 ; i+1 < n ; i++) {
		for(int j = 0 ; j < n ; j++) {
			int cur = i * n + j;

			for(int v : adj[j]) {
				int nex = (i+1) * n + v;
				network.add_edge(cur, nex, 1);
			}
		}
		network.add_edge((i+1) * n + (n-1), sink, n);

		int mf = network.maxFlow(k);
		// printf("%d %d\n", i, mf);

		if(mf < k) {
			k -= mf;
		} else {
			return i+1;
		}
	}

	return -1;
}

void reset() {
	for(int i = 1 ; i <= n ; i++)
		adj[i-1].clear();
}

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		printf("%d\n", solve());
		reset();
	}
	return 0;
}