#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second

const int N = 1e5 + 5;

struct node {
	int maks;
	int suf;
	int pref;
	int len;

	node operator +(node other) const {
		node ret;

		ret.maks = max(maks,other.maks);
		ret.maks = max(ret.maks,suf + other.pref);
		ret.len = len + other.len;

		// if full, combine
		ret.pref = (pref == len) ? pref + other.pref : pref;
		ret.suf = (other.suf == other.len) ? suf + other.suf : other.suf;

		return ret;
	}
};

node stree[4*N];
pii arr[N];
pair<pii,int> qu[N];
int lo[N], hi[N];
vector<int> proc[N];
int n, q;

void build(int id,int l,int r) {
	stree[id] = (node){0,0,0,1};
	if(l < r) {
		int m = (l + r) / 2;
		int chld = id << 1;

		build(chld,l,m);
		build(chld+1,m+1,r);
	}
}

void update(int id,int l,int r,int x) {
	if(l == r) {
		stree[id] = (node){1,1,1,1};
	}
	else {
		int m = (l + r) / 2;
		int chld = id << 1;

		if(x <= m)	update(chld,l,m,x);
		else		update(chld+1,m+1,r,x);

		stree[id] = stree[chld] + stree[chld+1];
	}
}

node query(int id,int l,int r,int x,int y) {
	if(x <= l && r <= y) {
		return stree[id];
	}
	else {
		int m = (l + r) / 2;
		int chld = id << 1;

		node ret;
		if(y <= m)		ret = query(chld,l,m,x,y);
		else if(x > m)	ret = query(chld+1,m+1,r,x,y);
		else			ret = query(chld,l,m,x,y) + query(chld+1,m+1,r,x,y);

		return ret;
	}
}

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d",&arr[i].fi);
		arr[i].se = i;
	}
	scanf("%d",&q);
	for(int i = 1 ; i <= q ; i++) {
		scanf("%d %d %d",&qu[i].fi.fi,&qu[i].fi.se,&qu[i].se);
	}
}

void solve() {
	sort(arr + 1,arr + n + 1);
	reverse(arr + 1,arr + n + 1);

	for(int i = 1 ; i <= q ; i++) {
		lo[i] = 1;
		hi[i] = n;
		proc[(1 + n) / 2].push_back(i);
	}

	bool change = 1;
	while(change) {
		change = 0;
		build(1,1,n);

		for(int i = 1 ; i <= n ; i++) {
			update(1,1,n,arr[i].se);

			while(!proc[i].empty()) {
				int idx = proc[i].back();
				proc[i].pop_back();

				if(query(1,1,n,qu[idx].fi.fi,qu[idx].fi.se).maks >= qu[idx].se)
					hi[idx] = i;
				else
					lo[idx] = i+1;

				if(lo[idx] < hi[idx]) {
					change = 1;
					proc[(lo[idx] + hi[idx]) / 2].push_back(idx);
				}
			}
		}
	}

	for(int i = 1 ; i <= q ; i++)
		printf("%d\n",arr[lo[i]].fi);
}

int main() {
	read();
	solve();
	return 0;
}