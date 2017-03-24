#include <bits/stdc++.h>
using namespace std;

void OPEN(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

void CLOSE() {
	fclose(stdin);
	fclose(stdout);
}

const int N = 1e5 + 5;

vector<int> adj[N];
vector<int> special;
int nxt[N];
int prv[N];
int pset[N];
int size[N];
int n, m;

void tutup() {
	CLOSE();
	exit(0);
}

void fail() {
	puts("There is no route, Karl!");
	tutup();
}

void read() {
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= m ; i++) {
		int u, v;
		scanf("%d %d",&u,&v);
		adj[u].push_back(v);
	}
}

int finds(int x) {
	while(pset[x] != x) x = pset[x];
	return x;
}

void init() {
	for(int i = 1 ; i <= n ; i++) {
		pset[i] = i;
		size[i] = 1;
	}
	if(m < n) {
		fail();
	}
	if(m == n) {
		set<int> seen;
		int now = 1;
		vector<int> v;

		while(!seen.count(now)) {
			v.push_back(now);
			seen.insert(now);
			//cerr << now << "\n";

			if(adj[now].size() != 1) {
				fail();
			}

			now = adj[now][0];
		}

		if(now == 1 && v.size() == n) {
			for(int x : v)
				printf("%d ", x);
			printf("1\n");
		} else {
			fail();
		}
		
		tutup();
	}
	for(int i = 1 ; i <= n ; i++) {
		if(adj[i].size() > 23) {
			fail();
		}
		if(adj[i].empty()) {
			fail();
		}
		if(adj[i].size() == 1) {
			int j = adj[i][0];

			if(prv[j] != 0) {
				fail();
			} else {
				int u = finds(i);
				int v = finds(j);
				if(size[u] > size[v]) {
					swap(u, v);
				}
				if(u != v) {
					size[v] += size[u];
					pset[u] = v;
				}
				nxt[i] = j;
				prv[j] = i;
			}
		} else {
			special.push_back(i);
		}
	}
}

void printSolution() {
	int now = 1;
	do {
		printf("%d ", now);
		now = nxt[now];
	} while(now != 1);
	printf("1\n");
	tutup();
}

void rec(int idx) {
	if(idx == special.size()) {
		if(size[finds(1)] == n) {
			printSolution();
			tutup();
		}
	} else {
		int now = special[idx];
		for(int x : adj[now]) {
			if(prv[x] == 0) {
				int u = finds(now);
				int v = finds(x);
				if(size[u] > size[v]) {
					swap(u, v);
				}
				if(u != v) {
					size[v] += size[u];
					pset[u] = v;
				}
				nxt[now] = x;
				prv[x] = now;
				rec(idx+1);
				if(u != v) {
					size[v] -= size[u];
					pset[u] = u;
				}
				prv[x] = 0;
				nxt[now] = 0;
			}
		}
	}
}

int main() {
	OPEN("king");
	read();
	init();
	rec(0);	
	fail();
	return 0;
}