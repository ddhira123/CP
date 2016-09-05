#include <bits/stdc++.h>
using namespace std;

const int N = 50005;
const int INF = (int)1e9;

long long jurang[N + 5];
long long height[N + 5];
int n,m;
int stree[4 * N];

void update(int id,int l,int r,int x,int val) {
	if(l == r) {
		stree[id] = val;
	}
	else {
		int mid = (l + r) / 2;
		int chld = id << 1;
		if(x <= mid)	update(chld,l,mid,x,val);
		else			update(chld + 1,mid + 1,r,x,val);
		stree[id] = min(stree[chld],stree[chld + 1]);
	}
} 

int query(int id,int l,int r,int x,int y) {
	if(x <= l && r <= y)
		return stree[id];
	else {
		int mid = (l + r) / 2;
		int chld = id << 1;
		int res = INF;
		if(x <= mid)	res = min(res,query(chld,l,mid,x,y));
		if(y > mid)		res = min(res,query(chld + 1,mid + 1,r,x,y));
		return res;	
	}	
}

void init() {
	scanf("%d %d",&n,&m);
	for(int i = 0 ; i < n ; i++) {
		scanf("%lld",&height[i]);
	}
	jurang[0] = height[0];
	for(int i = 1 ; i < n ; i++)
		jurang[i] = jurang[i - 1] + height[i] * 2;
}

void solve() {
	update(1,0,n - 1,n - 1,0);
	for(int i = n - 2 ; i >= 0 ; i--) {
		int rightMost = upper_bound(jurang,jurang + n,jurang[i] + height[i] * m * 2) - jurang;
		rightMost--;
		if(i == rightMost)
			update(1,0,n - 1,i,INF);
		else {
			int dpNow = query(1,0,n - 1,i + 1,rightMost) + 1;
			update(1,0,n - 1,i,dpNow);
		}	
	}
	int ret = query(1,0,n - 1,0,0);
	if(ret >= INF) ret = -1;
	printf("%d\n",ret);
}

int main() {
	int tc;
	scanf("%d",&tc);
	for(int t = 1 ; t <= tc ; t++) {
		init();
		solve();
	}
	return 0;
}
