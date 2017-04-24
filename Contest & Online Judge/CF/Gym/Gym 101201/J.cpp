#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 2e5 + 5;
const int LG = 18;

vector<LL> uniq;
int BIT[N];
LL arr[N];
int depth[N];
int anc[N][LG];
int n, q;

void update(int now, int val) {
	for(; now < N ; now += now & -now)
		BIT[now] = min(BIT[now], val);
}

int query(int x) {
	int ret = N;
	while(x) {
		ret = min(ret, BIT[x]);
		x -= x & -x;
	}
	return ret;
}

int getId(LL val) {
	return lower_bound(uniq.begin(), uniq.end(), val) - uniq.begin() + 1;
}

void build(int prv, int now) {
	depth[now] = depth[prv]+1;
	anc[now][0] = prv;

	for(int i = 1 ; (1<<i) <= depth[now] ; i++) {
		anc[now][i] = anc[anc[now][i-1]][i-1];
	}
}

void read() {
	scanf("%d %d", &n, &q);
	for(int i = 0 ; i < n ; i++) {
		scanf("%lld", arr + i);
	}
}

void prepare() {
	arr[n] = 0;
	for(int i = 0 ; i < N ; i++)
		BIT[i] = N;

	for(int i = 0 ; i <= n ; i++) {
		uniq.push_back(arr[i]);
	}
	sort(uniq.begin(), uniq.end());

	update(getId(0), n);

	for(int i = n-1 ; i >= 0 ; i--) {
		int idx = getId(arr[i]);

		int parent = query(idx-1);
		// printf("parent %d now %d\n", parent, i);
		build(parent, i);

		update(idx, i);
	}
}

int get(int cur, LL val) {
	for(int i = LG-1 ; i >= 0 ; i--)
		if(depth[cur] >= (1<<i) && arr[anc[cur][i]] > val) {
			cur = anc[cur][i];
		}
	return anc[cur][0];
}

LL solve(LL v, int l, int r) {
	l--; r--;

	v %= arr[l];
	int now = get(l, v);

	while(now <= r) {
		v %= arr[now];
		now = get(now, v);
	}

	return v;
}

void work() {
	for(int i = 0 ; i < q ; i++) {
		LL v;
		int l, r;

		scanf("%lld %d %d", &v, &l, &r);

		printf("%lld\n", solve(v, l, r));
	}
}

int main() {
	read();
	prepare();
	work();
	return 0;
}