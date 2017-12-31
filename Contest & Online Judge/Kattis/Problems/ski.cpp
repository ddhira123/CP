#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 5e5 + 5;

struct node {
	LL sum;
	LL maks;
	LL pref;
	LL suf;

	node operator +(node other) const {
		node res;

		res.sum = sum + other.sum;
		res.pref = max(pref,sum + other.pref);
		res.suf = max(other.suf,other.sum + suf);

		res.maks = max(maks, other.maks);
		res.maks = max(res.maks, suf + other.pref);
		return res;
	}
};

node stree[4*N];
LL BIT[N];
int H[N];
int n, q;

void updateBIT(int x,int val) {
	for(; x <= n ; x += x & -x)
		BIT[x] += val;
}

LL queryBIT(int x) {
	LL ret = 0;
	while(x) {
		ret += BIT[x];
		x -= x & -x;
	}
	return ret;
}

int getIndex(int x,LL k) {
	int lo = x, hi = n;
	LL haha = queryBIT(x-1);
	while(lo < hi) {
		int mid = (lo + hi + 1) / 2;
		LL ret = queryBIT(mid) - haha;
		ret *= 2;
		ret -= (H[x] + H[mid]);
		if(ret <= k) lo = mid;
		else hi = mid-1;
	}
	return lo;
}

LL getFun(LL a,LL b) {
	LL ret = (a-b)*(a-b);
	if(a < b) ret = -ret;
	return ret;
}

void build(int id,int l,int r) {
	if(l == r) {
		LL fun = getFun(H[l],H[l+1]);
		LL collapse = max(0LL,fun);
		stree[id] = (node){fun,collapse,collapse,collapse};
		//printf("%d %lld\n",l,fun);
	}
	else {
		int m = (l + r) / 2;
		int chld = id << 1;

		build(chld,l,m);
		build(chld+1,m+1,r);

		stree[id] = stree[chld] + stree[chld+1];
	}
}

void update(int id,int l,int r,int x) {
	if(l == r) {
		LL fun = getFun(H[l],H[l+1]);
		LL collapse = max(0LL,fun);
		stree[id] = (node){fun,collapse,collapse,collapse};
		//printf("%d %lld\n",l,fun);
	}
	else {
		int m = (l + r) / 2;
		int chld = id << 1;

		if(x <= m)	update(chld,l,m,x);
		else	update(chld + 1,m + 1,r,x);

		stree[id] = stree[chld] + stree[chld+1];
	}
}

node query(int id,int l,int r,int x,int y) {
	node ret;
	if(x <= l && r <= y)
		ret = stree[id];
	else {
		int m = (l + r) / 2;
		int chld = id << 1;

		if(x <= m && y > m) ret = query(chld,l,m,x,y) + query(chld+1,m+1,r,x,y);
		else if(x <= m)	ret = query(chld,l,m,x,y);
		else ret = query(chld + 1,m + 1,r,x,y);
	}
	//printf("%d %d %lld %lld %lld %lld\n",l,r,ret.sum,ret.maks,ret.pref,ret.suf); 
	return ret;
}

void updateWorker(int id,int x) {
	updateBIT(id,x-H[id]);
	H[id] = x;
	if(id < n) update(1,1,n-1,id);
	if(id > 1) update(1,1,n-1,id-1);
}

void queryWorker(int id,LL k) {
	int idx = getIndex(id,k);
	//printf("%d\n",idx);
	if(idx == 1) {
		printf("0\n");
		return;
	}
	node ret = query(1,1,n-1,1,idx-1);
	ret.maks = max(0LL,ret.maks);
	printf("%lld\n",ret.maks);
}

void init() {
	scanf("%d %d",&n,&q);
	n++;
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d",H + i);
		updateBIT(i,H[i]);
	}
	build(1,1,n-1);
}

void solve() {
	for(int i = 1 ; i <= q ; i++) {
		int opt; scanf("%d",&opt);
		if(opt == 0) {
			int a, b;
			scanf("%d %d",&a,&b);
			updateWorker(a+1,b);
		}
		else {
			int x;
			LL k;
			scanf("%d %lld",&x,&k);
			queryWorker(x+1,k);
		}
	}
}

int main() {
	init();
	solve();
	return 0;
}