#include <bits/stdc++.h>
using namespace std;

typedef pair<long long,long long> pii;
#define fi first
#define se second

bool cmp(pii a,pii b) {
	long long x = (a.fi) * b.se;
	long long y = (b.fi) * a.se;
	return x > y;
}

const int N = 100005;

vector<pii> stree[4*N];
vector<pii> psum[4*N];
int a[N], b[N];
long long aDoang[4*N];
long long bNol[4*N];
int n, q;

pii query(int id,pii x) {
	int lo = 0, hi = stree[id].size()-1;
	while(lo < hi) {
		int mid = (lo + hi + 1) / 2;
		if(cmp(stree[id][mid],x))
			lo = mid;
		else
			hi = mid-1;
	}
	//printf("lo %d %lld %lld %lld %lld\n",lo,stree[id][lo].fi,stree[id][lo].se,psum[id][lo].fi,psum[id][lo].se);
	return psum[id][lo];
} 

void add(int id,int l,int r,int x,pii val) {
	stree[id].push_back(val);
	if(l < r) {
		int m = (l + r) / 2;
		int chld = id << 1;
		if(x <= m) add(chld,l,m,x,val);
		else	   add(chld + 1,m + 1,r,x,val);
	}
}

void build(int id,int l,int r) {
	stree[id].push_back({1e7,1});
	sort(stree[id].begin(),stree[id].end(),cmp);
	psum[id].push_back({0,0});
	pii lst = {0,0};
	for(int i = 1 ; i < stree[id].size() ; i++) {
		pii x = stree[id][i];
		//printf("id %d l %d r %d %lld %lld\n",id,l,r,x.fi,x.se);
		psum[id].push_back({x.fi + lst.fi,x.se + lst.se});
		lst = psum[id].back();
	}

	if(l < r) {
		int m = (l + r) / 2;
		int chld = id << 1;
		build(chld,l,m);
		build(chld + 1,m + 1,r);
	}
}

pii query(int id,int l,int r,int x,int y,pii z) {
	if(x <= l && r <= y) return query(id,z);
	else {
		int m = (l + r) / 2;
		int chld = id << 1;
		pii ret = {0,0};
		pii temp;

		if(x <= m) {
			temp = query(chld,l,m,x,y,z);
			ret = {ret.fi + temp.fi,ret.se + temp.se};
		}
		if(y > m) {
			temp = query(chld+1,m+1,r,x,y,z);
			ret = {ret.fi + temp.fi,ret.se + temp.se};
		}

		return ret;
	}
}

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) scanf("%d",a + i);
	for(int i = 1 ; i <= n ; i++) scanf("%d",b + i);
}

void prepare() {
	for(int i = 1 ; i <= n ; i++) {
		aDoang[i] = aDoang[i-1] + a[i];
		bNol[i] = bNol[i-1];
		if(b[i] != 0) add(1,1,n,i,{a[i],b[i]});
		else bNol[i] += a[i];
	}
	//cerr << "build\n";
	build(1,1,n);
	//cerr << "done\n";
}

void solve() {
	scanf("%d",&q);
	for(int i = 1 ; i <= q ; i++) {
		int l, r, c, d;
		scanf("%d %d %d %d",&l,&r,&c,&d);
		long long ret = 0;

		if(c == 0) ret = 0;
		else if(d == 0) ret = (aDoang[r] - aDoang[l-1]) * c;
		else {
			pii temp = query(1,1,n,l,r,{d,c});
			ret = (temp.fi + bNol[r] - bNol[l-1]) * c - temp.se * d;
		}

		printf("%lld\n",ret);
		fflush(stdout);
	}
}

int main() {
	read();
	prepare();
	solve();
	return 0;
}