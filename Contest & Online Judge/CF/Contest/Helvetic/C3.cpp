#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int LOG = 18;

int anc[N][LOG];
int depth[N];
int n;
int arr[N];

void build() {
	for(int lg = 1 ; lg < LOG ; lg++)
		for(int i = 1 ; i <= n ; i++)
			if(depth[i] >= (1<<lg)) {
				int papa = anc[i][lg-1];
				anc[i][lg] = anc[papa][lg-1];
			}
}

int getLCA(int u,int v) {
	if(depth[u] < depth[v]) swap(u,v);
	int diff = depth[u] - depth[v];

	for(int i = 0 ; diff > 0 ; i++)
		if(diff & (1<<i)) {
			diff -= (1<<i);
			u = anc[u][i];
		} 

	if(u == v) return u;

	for(int i = LOG - 1 ; i >= 0 ; i--)
		if(depth[u] >= (1<<i) && anc[u][i] != anc[v][i]) {
			u = anc[u][i];
			v = anc[v][i];
		}

	return anc[u][0];	
}

int getDist(int u,int v) {
	return depth[u] + depth[v] - 2*depth[getLCA(u,v)];
}

void init() {
	scanf("%d",&n);
	for(int i = 2 ; i <= n ; i++) {
		scanf("%d",&anc[i][0]);
		depth[i] = depth[anc[i][0]] + 1;
	}
	build();
}

void solve() {
	int a = 1, b = 2;
	printf("1");
	for(int i = 3 ; i <= n ; i++) {
		printf(" ");
		int cur = getDist(a,b);
		int withA = getDist(a,i);
		int withB = getDist(b,i);
		int mx = max(withA,withB);

		if(cur < mx) {
			if(mx == withA) b = i;
			else a = i;
			cur = mx;
		}

		printf("%d",cur);
	}
	puts("");
}

int main() {
	init();
	solve();
	return 0;
}