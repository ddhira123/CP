#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const long long INF = 1e9;

struct edge {
	long long flow;
	int cost;
	int from;
	int to;
};


vector<edge> elist;
vector<int> adj[3*N];
int dist[N][N];
int n, k;

long long flow_dist[3*N];
bool in_q[3*N];
int source, sink;
int prv[3*N];

void add_edge(int from, int to, int flow, int cost) {
	adj[from].push_back(elist.size());
	elist.push_back((edge){flow, cost, from, to});

	adj[to].push_back(elist.size());
	elist.push_back((edge){0, -cost, to, from});
}

bool SPFA() {
	for(int i = source ; i <= sink ; i++) {
		flow_dist[i] = INF;
		prv[i] = -1;
	}

	flow_dist[source] = 0;
	queue<int> q;
	q.push(source);
	in_q[source] = 1;

	while(!q.empty()) {
		int now = q.front();
		q.pop();

		in_q[now] = 0;
		// printf("%d\n", now);
		for(int idx : adj[now]) {
			edge cur_edge = elist[idx];
			int to = cur_edge.to;
			int flow = cur_edge.flow;
			int cost = cur_edge.cost;

			if(flow > 0 && flow_dist[now] + cost < flow_dist[to]) {
				flow_dist[to] = flow_dist[now] + cost;
				prv[to] = idx;

				if(!in_q[to]) {
					in_q[to] = 1;
					q.push(to);
				}
			}
		}
	}

	// printf("hehe\n");
	return prv[sink] != -1;
}

int augment(int now, int f) {
	if(now == source) return f;
	int idx = prv[now];
	int fr = elist[idx].from;
	int flow = elist[idx].flow;

	int ret = augment(fr, min(flow, f));

	elist[idx].flow -= ret;
	elist[idx^1].flow += ret;
	// printf("lewat %d\n", now);
	return ret;
}

pair<int,long long> min_cost_max_flow() {
	pair<int,long long> ret = {0, 0};

	while(SPFA()) {
		// printf("dist sink %d \n", flow_dist[sink]);
		int flow = augment(sink, INF);

		ret.first += flow;
		ret.second += (flow * flow_dist[sink]);
		// printf("flow %d\n", flow);
	}

	return ret;
}

void read() {
	cin >> n >> k;
	for(int i = 1 ; i <= n ; i++) {
		for(int j = i+1 ; j <= n+1 ; j++)
			cin >> dist[i][j];
	}	
}

void warshall() {
	for(int i = 1 ; i <= n+1 ; i++) {
		for(int j = 1 ; j < i ; j++)
			dist[i][j] = INF;
		dist[i][i] = 0;
	}

	for(int i = 1 ; i <= n+1 ; i++)
		for(int j = 1 ; j <= n+1 ; j++)
			for(int ii = 1 ; ii <= n+1 ; ii++) {
				dist[ii][j] = min(dist[ii][j], dist[ii][i] + dist[i][j]);
			}
}

void make_flow_graph() {
	source = 0;
	sink = 2*n + 3;

	// warshall();

	add_edge(source, 1, k, 0);
	for(int i = 2 ; i <= n+1 ; i++)
		add_edge(source, i, 1, 0);

	for(int i = 1 ; i <= n+1 ; i++)
		for(int j = i+1 ; j <= n+1 ; j++)
			add_edge(i, n+1+j, 1, dist[i][j]);

	for(int i = 1 ; i <= n+1 ; i++)
		add_edge(n+1+i, sink, 1, 0);
} 

int main() {
	read();
	make_flow_graph();
	pair<int, long long> ret = min_cost_max_flow();
	assert(ret.first == n);

	printf("%lld\n", ret.second);
	return 0;
}