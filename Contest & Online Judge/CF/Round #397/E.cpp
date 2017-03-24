#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

vector<int> adj[N];
int deg[N];
int rusak[N];
int ukuran[N];
int hi[N];
int n;

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i < n ; i++) {
		int u, v;
		scanf("%d %d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);

		deg[u]++;
		deg[v]++;
	}
}

void solve() {
	queue<int> q;

	for(int i = 1 ; i <= n ; i++)
		if(deg[i] == 1)
			q.push(i);

	int now;
	while(!q.empty()) {
		now = q.front();
		q.pop();
		deg[now] = 0;

		set<int> st;
		for(int nex : adj[now]) {
			if(deg[nex] == 0) {
				if(ukuran[nex]) {
					rusak[now] = 1;
					ukuran[now] = 2;
				} else {
					st.insert(hi[nex]+1);
				}
			} else {
				deg[nex]--;
				if(deg[nex] == 1) {
					q.push(nex);
				}
			}
		}

		if(st.size() > 1) {
			ukuran[now] = st.size();
			for(int x : st)
				rusak[now] += x;
		} else {
			hi[now] = st.empty() ? 0 : *st.begin();
		}
	}

	int fail = 0;
	for(int i = 1 ; i <= n ; i++)
		if(ukuran[i])
			fail++;

	int ans = -1;
	if(fail == 0) {
		ans = hi[now];
		while(ans % 2 == 0) ans /= 2;
	} else if(fail == 1 && ukuran[now] == 2) {
		ans = rusak[now];
		while(ans % 2 == 0) ans /= 2;
	}

	printf("%d\n", ans);
}

int main() {
	read();
	solve();
	return 0;
}