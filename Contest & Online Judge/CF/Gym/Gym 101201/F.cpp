#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

const int N = 1e3 + 5;

int n, r, k;
int x[N], y[N];
int pset[2*N];

vector<int> adj[2*N];

int getId(int a, int b) {
	return 2 * a + b;
}

vector<int> stek;
int num[N<<1], low[N<<1], stat[2*N];
int scc[N<<1];
int sccCount;
int cnt;

void dfs(int now) {
	stek.push_back(now);
	num[now] = low[now] = ++cnt;
	stat[now] = 1;

	for(int nex : adj[now]) {
		if(stat[nex] == -1) dfs(nex);
		if(stat[nex] == 1) {
			low[now] = min(low[now], low[nex]);
		}
	}

	if(low[now] == num[now]) {
		sccCount++;
		int cur;
		do {
			cur = stek.back();
			stek.pop_back();
			stat[cur] = 0;
			scc[cur] = sccCount;
		} while(cur != now);
	}
}

void read() {
	cin >> n >> r >> k;
	for(int i = 0 ; i < k ; i++)
		cin >> x[i] >> y[i];
}

void makeGraph() {
	for(int i = 0 ; i < k ; i++) {
		for(int j = 0 ; j < k ; j++) {
			if(i == j) continue;
			// vertikal

			if(y[i] == y[j] && (x[i] <= x[j] && x[i] + r >= x[j] - r)) {
				int a0 = getId(i, 0);
				int a1 = getId(i, 1);

				int b0 = getId(j, 0);
				int b1 = getId(j, 1);

				adj[a0].push_back(b1);
				adj[b0].push_back(a1);
			}

			// horizontal
			if(x[i] == x[j] && (y[i] <= y[j] && y[i] + r >= y[j] - r)) {
				int a0 = getId(i, 0);
				int a1 = getId(i, 1);

				int b0 = getId(j, 0);
				int b1 = getId(j, 1);

				adj[a1].push_back(b0);
				adj[b1].push_back(a0);
			}
		}
	}
}

bool check() {
	memset(stat, -1, sizeof stat);

	for(int i = 0 ; i < k ; i++)
		for(int j = 0 ; j < 2 ; j++) {
			int cur = getId(i, j);

			if(stat[cur] == -1) {
				dfs(cur);
			}
		}

	for(int i = 0 ; i < k ; i++)
		if(scc[getId(i, 0)] == scc[getId(i, 1)])
			return false;

	return true;
}

int main() {
	read();
	makeGraph();
	printf("%s\n", check() ? "YES" : "NO");
	return 0;
}