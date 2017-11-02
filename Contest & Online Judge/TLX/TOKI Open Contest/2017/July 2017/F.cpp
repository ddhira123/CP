#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int color[N];
int answer[N];
int n, k;
vector<int> adj[N];
map<int, int> m[N];
int depth[N];
int refer[N];

void read() {
	scanf("%d %d", &n, &k);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d", color + i);
	for(int i = 1 ; i < n ; i++) {
		int u, v;
		scanf("%d %d", &u, &v);

		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

void prepare() {
	for(int i = 1 ; i <= n ; i++) {
		refer[i] = i;
	}
}

void dfs(int now, int prv) {
	m[now][color[now]] = depth[now];
	for(int nex : adj[now]) {
		if(nex == prv) continue;
		depth[nex] = depth[now]+1;
		dfs(nex, now);
		int a = refer[now];
		int b = refer[nex];
		// printf("merging %d nd %d\n", now, nex);
		if(m[a].size() >= m[b].size()) {
			for(auto it : m[b]) {
				// printf("%d -> %d\n", it.first, it.second);
				if(m[a].count(it.first)) {
					// printf("%d\n", m[a][it.first]);
					answer[it.first] = max(answer[it.first], m[a][it.first] + it.second - 2 * depth[now]);
				}
				m[a][it.first] = max(m[a][it.first], it.second);
			}
			m[b].clear();
		} else {
			for(auto it : m[a]) {
				// printf("%d -> %d\n", it.first, it.second);
				if(m[b].count(it.first)) {
					// printf("%d\n", m[b][it.first]);
					answer[it.first] = max(answer[it.first], m[b][it.first] + it.second - 2 * depth[now]);
				}
				m[b][it.first] = max(m[b][it.first], it.second);
			}
			m[a].clear();
			refer[now] = b;
		}
	}
}

void solve() {
	dfs(1, -1);
	for(int i = 1 ; i <= k ; i++) {
		// printf("%d %d\n", i, answer[i]);
		answer[i] = (answer[i] + 1) / 2;

		printf("%d%c", answer[i], i == k ? '\n' : ' ');
	}
}

int main() {
	read();
	prepare();
	solve();
	return 0;
}