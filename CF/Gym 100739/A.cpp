#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

const int N = 100005;
const int MOD = 4001;

struct node {
	int val[2];
	int lazy;

	node() {
		val[0] = val[1] = lazy = 0;
	}

	int get(int x) {
		return val[(x + lazy) & 1];
	}

	node operator +(node other) {
		node res;
		res.lazy = 0;
		res.val[0] = get(0) + other.get(0);
		res.val[1] = get(1) + other.get(1);
		return res;
	}
};

node stree[10][4*N];
int arr[N];
int pxor[N];
int comb[MOD][MOD];
int n,q;

void build(int id,int l,int r) {
	if(l == r) {
		for(int i = 0 ; i < 10 ; i++)
			if(pxor[l] & (1<<i))
				stree[i][id].val[1] = 1;
			else
				stree[i][id].val[0] = 1;
	}
	else {
		int chld = id << 1;
		int m = (l + r) / 2;
		build(chld,l,m);
		build(chld + 1,m + 1,r);
		for(int i = 0 ; i < 10 ; i++) {
			stree[i][id] = stree[i][chld] + stree[i][chld + 1];
		}
	}
}

void propagate(int bit,int id) {
	if(stree[bit][id].lazy == 0) return;
	int chld = id << 1;
	for(int i = 0 ; i < 2 ; i++) {
		stree[bit][chld + i].lazy++;
		stree[bit][chld + i].lazy &= 1;
	}
	stree[bit][id].lazy = 0;
}

void update(int bit,int id,int l,int r,int x,int y) {
	if(x <= l && r <= y) {
		stree[bit][id].lazy++;
		stree[bit][id].lazy %= 2;
	}
	else {
		propagate(bit,id);
		int chld = id << 1;
		int m = (l + r) / 2;
		if(x <= m)	update(bit,chld,l,m,x,y);
		if(y > m)	update(bit,chld + 1,m + 1,r,x,y);
		stree[bit][id] = stree[bit][chld] + stree[bit][chld + 1];
	}
}

node query(int bit,int id,int l,int r,int x,int y) {
	if(x <= l && r <= y) {
		return stree[bit][id];
	}
	else {
		propagate(bit,id);
		int chld = id << 1;
		int m = (l + r) / 2;
		node res;

		if(x <= m) res = res + query(bit,chld,l,m,x,y);
		if(y > m)  res = res + query(bit,chld + 1,m + 1,r,x,y);

		stree[bit][id] = stree[bit][chld] + stree[bit][chld + 1];
		return res;	
	}
}

void read() {
	scanf("%d %d",&n,&q);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d",arr + i);
		pxor[i] = pxor[i-1] ^ arr[i];
	}
}

void prepare() {
	memset(comb,-1,sizeof comb);
	build(1,0,n);
}

int answer(int l,int r) {
	int ans = 0;
	for(int i = 0 ; i < 10 ; i++) {
		node ret = query(i,1,0,n,l-1,r);
		LL nol = ret.get(0);
		LL satu = ret.get(1);
		int temp = (satu * nol) % MOD;
		ans = (ans + temp * (1<<i)) % MOD;
	}
	return ans;
}

void updater(int idx,int x) {
	int temp = x ^ arr[idx];
	for(int i = 0 ; i < 10 ; i++)
		if(temp & (1 << i))
			update(i,1,0,n,idx,n);
	arr[idx] = x;	
}

void solve() {
	while(q--) {
		int opt,l,r;
		scanf("%d %d %d",&opt,&l,&r);
		if(opt == 1)
			updater(l,r);
		else
			printf("%d\n",answer(l,r));
	}
}

int main() {
	read();
	prepare();
	solve();
	return 0;
}