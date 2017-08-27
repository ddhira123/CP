#include <bits/stdc++.h>
using namespace std;

const int MAGIC = 300;
const int N = 1e5 + 5;
const int LOG = 18;

vector<int> bucket;
long long val[N];
long long added_val[N];
vector<int> chld[N];
int anc[N][LOG];
int depth[N];

long long last_q;
int n = 1;
int q;

int get_parent(long long x) {
	return last_q ^ x;
}

void dfs_remake(int prv, int now) {
	added_val[now] = val[now];
	for(int nex : chld[now]) {
		if(nex == prv) continue;
		dfs_remake(now, nex);
		added_val[now] += added_val[nex];
	}
}

void remake() {
	dfs_remake(-1, 1);
	bucket.clear();
}

void build(int now, int prv) {
	anc[now][0] = prv;
	depth[now] = depth[prv] + 1;
	for(int i = 1 ; (1 << i) <= depth[now] ; i++)
		anc[now][i] = anc[anc[now][i-1]][i-1];
}

int get_kth(int x, int k) {
	for(int i = 0 ; k ; i++)
		if(k & (1 << i)) {
			k -= (1 << i);
			x = anc[x][i];
		}
	return x;
}

long long query(int v) {
	long long ret = added_val[v];
	for(int x : bucket)
		if(depth[x] >= depth[v] && get_kth(x, depth[x] - depth[v]) == v) {
			// printf("%d -> %d\n", v, x);
			ret += val[x];
		}
	return ret;
}

int main() {
	scanf("%d", &q);
	for(int i = 1 ; i <= q ; i++) {
		int opt;
		scanf("%d", &opt);

		if(opt == 1) {
			long long u;
			scanf("%lld", &u);

			int par = get_parent(u);
			build(++n, par);
			scanf("%lld", &val[n]);

			// printf("%d parent %d val %lld\n", n, par, val[n]);

			chld[par].push_back(n);
			bucket.push_back(n);
			if(bucket.size() > MAGIC) {
				remake();
			}
		} else {
			int x; scanf("%d", &x);
			last_q = query(x);
			printf("%lld\n", last_q);
		}
	}
	return 0;
}