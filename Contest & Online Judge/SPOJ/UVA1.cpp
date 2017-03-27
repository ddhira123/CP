#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int Q = 20005;

struct query{
	int r1;
	int r2;
	int idx;

	bool operator <(query other) const {
		return r1 < other.r1;
	}
};

vector<int> uniq;
int BIT[N + Q];
int x[N], y[N];
pair<int,int> arr[N];
int ans[Q];
int xa,ya,xb,yb;
query kuery[Q];
int n,q;

int sqr(int z) {
	return z * z;
}

int getDist(int a,int b,int c,int d) {
	return sqr(a-c) + sqr(b-d);
}

void make(vector<int> &x) {
	sort(x.begin(),x.end());
	x.erase(unique(x.begin(),x.end()),x.end());
}

int getIDX(int x) {
	return lower_bound(uniq.begin(),uniq.end(),x) - uniq.begin();
}

void update(int x,int val) {
	for(; x < uniq.size() ; x += x & -x)
		BIT[x] += val;
}

int queryBIT(int x) {
	int ret = 0;
	while(x) {
		ret += BIT[x];
		x -= x & -x;
	}
	return ret;
}

bool read() {
	scanf("%d",&n);
	if(n == 0) return 0;
	for(int i = 1 ; i <= n ; i++)
		scanf("%d %d",x + i,y + i);
	scanf("%d %d %d %d %d",&xa,&ya,&xb,&yb,&q);
	for(int i = 1 ; i <= q ; i++) { 
		scanf("%d %d",&kuery[i].r1,&kuery[i].r2);
	}	
	return 1;
}

void init() {
	uniq.clear();
	uniq.push_back(-1);
	for(int i = 1 ; i <= n ; i++) {
		arr[i].first = getDist(x[i],y[i],xa,ya);
		arr[i].second = i;
		uniq.push_back(getDist(x[i],y[i],xb,yb));
	}
	for(int i = 1 ; i <= q ; i++) {
		kuery[i].r1 = sqr(kuery[i].r1);
		kuery[i].r2 = sqr(kuery[i].r2);
		kuery[i].idx = i;
		uniq.push_back(kuery[i].r2);
	}

	make(uniq);
	for(int i = 0 ; i < uniq.size() ; i++)
		BIT[i] = 0;
	sort(arr + 1,arr + n + 1);
	sort(kuery + 1,kuery + q + 1);
}

void solve() {
	for(int i = 1,last = 1 ; i <= q ; i++) {
		while(last <= n && kuery[i].r1 >= arr[last].first) {
			int pos = arr[last].second;
			int dist = getDist(x[pos],y[pos],xb,yb);
			int idx = getIDX(dist);
			update(idx,1);
			last++;
		}
		ans[kuery[i].idx] = queryBIT(getIDX(kuery[i].r2));
	}
	for(int i = 1 ; i <= q ; i++)
		printf("%d\n",ans[i]);
}

int main() {
	int tc = 0;
	while(read()) {
		printf("Case %d:\n",++tc);
		init();
		solve();
	}
	return 0;
}