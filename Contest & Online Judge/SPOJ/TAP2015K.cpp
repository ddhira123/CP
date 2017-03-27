#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second

const int N = 50005;

set<pii> s;
int arr[N];
int n,q;

int stree[4 * N];

int getNext(pii x) {
	auto it = s.upper_bound(x);
	if(it == s.end() || (*it).fi != x.fi)
		return n+1;
	return (*it).se;
}

int getPrev(pii x) {
	auto it = s.lower_bound(x);
	if(it == s.begin()) return 0;
	it--;
	if((*it).fi != x.fi) return 0;
	return (*it).se;
}

void update(int id,int l,int r,int x,int y) {
	if(l == r) {
		stree[id] = y;
	}
	else {
		int chld = id << 1;
		int m = (l + r) / 2;
		if(x <= m)	update(chld,l,m,x,y);
		else		update(chld + 1,m + 1,r,x,y);
		stree[id] = max(stree[chld],stree[chld + 1]);
	}
}

int query(int id,int l,int r,int x,int y) {
	if(x <= l && r <= y) {
		return stree[id];
	}
	else {
		int chld = id << 1;
		int m = (l + r) / 2;
		int ret = 0;
		if(x <= m)	ret = max(ret,query(chld,l,m,x,y));
		if(y > m)	ret = max(ret,query(chld + 1,m + 1,r,x,y));
		return ret;	
	}
}

void change(int pos,int newVal) {
	pii x = {arr[pos],pos};
	int nxt = getNext(x);
	int prv = getPrev(x);
	update(1,1,n + 1,nxt,prv);
	s.erase(x);

	arr[pos] = newVal;
	x.fi = newVal;
	s.insert(x);
	nxt = getNext(x);
	prv = getPrev(x);
	update(1,1,n + 1,pos,prv);
	update(1,1,n + 1,nxt,pos);	
}

bool read() {
	if(scanf("%d %d",&n,&q) != 2) return 0;
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d",arr + i);
	}
	return 1;
}

void init() {
	for(int i = 1 ; i <= n ; i++) {
		pii x = {arr[i],i};
		s.insert(x);
		int prv = getPrev(x);
		update(1,1,n + 1,i,prv);
	}
}

void solve() {
	for(int i = 1 ; i <= q ; i++) {
		char opt[5];
		scanf("%s",opt);

		if(opt[0] == 'E') {
			int pos; scanf("%d",&pos);
			printf("%d\n",pos - query(1,1,n + 1,1,pos));
		}
		else {
			int pos,newVal;
			scanf("%d %d",&pos,&newVal);
			change(pos,newVal);
		}
	}
}

void reset() {
	s.clear();
}

int main() {
	while(read()) {
		init();
		solve();
		reset();
	}
	return 0;
}