#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 5;

struct query {
	int opt;
	int u;
	int v;
};

query arr[N];
int pset[N], score[N];

int u[N], v[N];
int lo[N], hi[N];
vector<int> proc[N];
vector<int> update[N];

int n,m,q;

int finds(int x) {
	return x == pset[x] ? x : pset[x] = finds(pset[x]);
}

void join(int x,int y) {
	x = finds(x); y = finds(y);
	if(x == y) return;
	score[x] += score[y];
	pset[y] = x;
}

void init() {
	for(int i = 1 ; i <= n ; i++) {
		pset[i] = i;
		score[i] = 0;
	}
}

void makeUpdate() {
	for(int i = 0 ; i < m ; i++) {
		lo[i] = 0;
		hi[i] = q;
		proc[(lo[i] + hi[i]) / 2].push_back(i);
	}

	bool change = 1;
	while(change) {
		change = 0;
		init();

		for(int i = 0 ; i < q ; i++) {
			if(arr[i].opt == 1) {
				join(arr[i].u,arr[i].v);
			}

			while(!proc[i].empty()) {
				int now = proc[i].back();
				proc[i].pop_back();

				if(finds(u[now]) == finds(v[now]))
					hi[now] = i;
				else
					lo[now] = i + 1;

				if(lo[now] < hi[now]) {
					change = 1;
					proc[(lo[now] + hi[now]) / 2].push_back(now);
				}
			}
		}
	}

	for(int i = 0 ; i < m ; i++)
		update[lo[i]].push_back(i);
}

void read() {
	scanf("%d %d %d",&n,&m,&q);

	for(int i = 0 ; i < m ; i++) {
		scanf("%d %d",u + i,v + i);
	}

	for(int i = 0 ; i < q ; i++) {
		scanf("%d %d",&arr[i].opt,&arr[i].u);
		if(arr[i].opt == 1) {
			scanf("%d",&arr[i].v);
		}
	}
}

void solve() {
	init();

	for(int i = 0 ; i < q ; i++) {
		if(arr[i].opt == 1) {
			join(arr[i].u,arr[i].v);
		}

		for(int iter : update[i]) {
			score[finds(u[iter])]++;
		}

		if(arr[i].opt == 2) {
			printf("%d\n",score[finds(arr[i].u)]);
		}
	}	
}

void reset() {
	for(int i = 0 ; i <= q ; i++) {
		update[i].clear();
	}
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		makeUpdate();
		solve();
		reset();
	}
	return 0;
}