#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 5;
const int LOG = 17;
const int INF = 1e9;
const int QUERY_SIZE = 5;

int anc[N][LOG];
int depth[N];
int dist[N];

int in[N], ot[N];
int cnt;

vector<pair<int,int>> adj[N];
int n, q;

void build(int now, int prv, int w) {
	anc[now][0] = prv;
	depth[now] = depth[prv] + 1;
	dist[now] = dist[prv] + w;

	for(int i = 1 ; (1<<i) <= depth[now] ; i++) {
		int papa = anc[now][i-1];
		anc[now][i] = anc[papa][i-1];
	}
}

void dfs(int now, int prv) {
	in[now] = ++cnt;
	for(pair<int,int> nex : adj[now]) {
		if(nex.first == prv) continue;

		build(nex.first, now, nex.second);
		dfs(nex.first, now);
	}
	ot[now] = cnt;
}

int getLCA(int u, int v) {
	if(depth[u] < depth[v]) swap(u, v);

	int diff = depth[u] - depth[v];
	for(int i = 0 ; diff ; i++)
		if(diff & (1<<i)) {
			diff -= (1 << i);
			u = anc[u][i];
		}

	if(u == v) return u;

	for(int i = LOG-1 ; i >= 0 ; i--)
		if(depth[u] >= (1<<i) && anc[u][i] != anc[v][i]) {
			u = anc[u][i];
			v = anc[v][i];
		}

	return anc[u][0];
}

int getDist(int u, int v) {
	return dist[u] + dist[v] - 2*dist[getLCA(u, v)];
}

bool cmp(int a, int b) {
	return in[a] < in[b];
}

int calc(vector<int> v) {
	sort(v.begin(), v.end(), cmp);
	int sz = v.size();

	for(int i = 1 ; i < sz ; i++)
		v.push_back(getLCA(v[i-1], v[i]));

	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());

	vector<int> minDist(v.size(), INF);
	vector<bool> taken(v.size(), false);
	minDist[0] = 0;

	int ret = 0;
	for(int i = 0 ; i < v.size() ; i++) {
		int mins = INF + 5;
		int pos = -1;

		for(int j = 0 ; j < v.size() ; j++)
			if(minDist[j] < mins && !taken[j]) {
				pos = j;
				mins = minDist[j];
			}

		ret += mins;
		taken[pos] = 1;

		for(int j = 0 ; j < v.size() ; j++)
			minDist[j] = min(minDist[j], getDist(v[pos], v[j]));
	}

	return ret;
}

void read() {
	scanf("%d", &n);	
	for(int i = 1 ; i < n ; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
}

void prepare() {
	dfs(0, -1);
}

void work() {
	scanf("%d", &q);
	for(int i = 0 ; i < q ; i++) {
		vector<int> query(QUERY_SIZE);

		for(int j = 0 ; j < QUERY_SIZE ; j++)
			scanf("%d", &query[j]);

		printf("%d\n", calc(query));
	}
}

int main() {
	read();
	prepare();
	work();
	return 0;
}