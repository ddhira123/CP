#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int INF = (int)2e9;

int stree[4 * N];
int BIT[N];

int realPos[N];
int pos[N];
int arr[N];
int n,q;

int sz;
int lg;

char opt[N][5];
int x[N];
int y[N];

void update(int x,int val) {
	for(; x <= sz ; x += x & -x) {
		BIT[x] += val;
	}
}

int getKth(int kth) {

	int now = 0;
	for(int i = lg ; i >= 0 ; i--)
		if(now + (1 << i) <= sz && BIT[now + (1 << i)] < kth) {
			now += (1 << i);
			kth -= BIT[now];
		}

	return now + 1;	
}

void build(int id,int l,int r) {
	if(l == r) {
		stree[id] = -INF;
	}
	else {
		int chld = id << 1;
		int m = (l + r) / 2;

		build(chld,l,m);
		build(chld + 1,m + 1,r);

		stree[id] = max(stree[chld],stree[chld + 1]);
	}
}

void updateStree(int id,int l,int r,int a,int b) {
	if(l == r) {
		stree[id] = b;
	}
	else {
		int chld = id << 1;
		int m = (l + r) / 2;

		if(a <= m)		updateStree(chld,l,m,a,b);
		else			updateStree(chld + 1,m + 1,r,a,b);

		stree[id] = max(stree[chld],stree[chld + 1]);		
	}
}

int queryStree(int id,int l,int r,int a,int b) {
	if(a <= l && r <= b) {
		return stree[id];
	}
	else {
		int chld = id << 1;
		int m = (l + r) / 2;

		int ret = -INF;
		if(a <= m)		ret = max(ret,queryStree(chld,l,m,a,b));
		if(b > m)		ret = max(ret,queryStree(chld + 1,m + 1,r,a,b));

		return ret;
	}
}

void read() {
	scanf("%d",&q);
	for(int i = 1 ; i <= q ; i++) {
		scanf("%s %d %d",opt[i],x + i,y + i);
		if(opt[i][0] == 'A') {
			n++;
			realPos[n] = y[i];
			arr[n] = x[i];
		}
	}
}

void init() {
	sz = n;
	n = 0;

	while((1 << lg) <= sz) lg++;
	lg--;

	for(int i = 1 ; i <= sz ; i++)
		update(i,1);

	for(int i = sz ; i >= 1 ; i--) {
		int place = getKth(realPos[i]);
		pos[i] = place;
		//printf("%d -> %d\n",i,place);
		update(place,-1);
	}

	build(1,1,sz);

}

void solve() {
	for(int i = 1 ; i <= q ; i++)
		if(opt[i][0] == 'A') {
			n++;
			//printf("pos %d arr %d\n",pos[n],arr[n]);
			updateStree(1,1,sz,pos[n],arr[n]);
			update(pos[n],1);
		}
		else {
			int l = x[i];
			int r = y[i];
			l = getKth(l);
			r = getKth(r);
			//printf("querying %d %d\n",l,r);
			printf("%d\n",queryStree(1,1,sz,l,r));
		}
}

int main() {
	read();
	init();
	solve();
	return 0;
}