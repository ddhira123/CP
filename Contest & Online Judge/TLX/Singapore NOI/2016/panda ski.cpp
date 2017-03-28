#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 200005;
const int MAXX = 100000;

struct node {
	vector<pair<int,LL> > stek;

	node() {
		stek.clear();
		stek.push_back({0,0});
	}

	void push(int y, LL val) {
		while(!stek.empty() && stek.back().second <= val) stek.pop_back();
		stek.push_back({y,val});
	}

	LL query(int y) {
		pair<int,LL> temp = {y,0};
		int idx = lower_bound(stek.begin(),stek.end(),temp) - stek.begin();
		if(idx == stek.size()) return 0;
		return stek[idx].second;
	}
};

struct gate {
	int x;
	int y;
	int s;
	int e;

	bool operator <(gate other) const {
		return y == other.y ? x < other.x : y < other.y;
	}

	void scan() {
		scanf("%d %d %d %d",&x,&y,&s,&e);
	}
};

node stree[4 * MAXX + 1000];
gate arr[N];
LL dp[N];
int n,h;

void update(int id,int l,int r,int xl,int xr,int y,LL val) {
	stree[id].push(y,val);
	if(xl <= l && r <= xr) {

	}
	else {
		int chld = id << 1;
		int m = (l + r) / 2;
		if(xl <= m)	update(chld,l,m,xl,xr,y,val);
		if(xr > m)	update(chld + 1,m + 1,r,xl,xr,y,val);
	}
}

LL query(int id,int l,int r,int xl,int xr,int y) {
	LL ret = 0;
	if(xl <= l && r <= xr) {
		ret = stree[id].query(y);
		//printf("GET %d %d %d ret %lld\n",l,r,y,ret);
	}
	else {
		int m = (l + r) / 2;
		int chld = id << 1;
		if(xl <= m)	ret = max(ret,query(chld,l,m,xl,xr,y));
		if(xr > m)	ret = max(ret,query(chld + 1,m + 1,r,xl,xr,y));
	}
	return ret;
}

int main() {
	scanf("%d %d",&n,&h);
	for(int i = 0 ; i < n ; i++) {
		arr[i].scan();
		arr[i].x += 50000;
	}
	sort(arr,arr + n);
	for(int i = 0 ; i < n ;) {
		int j = i;
		vector<pair<int,int> > range;
		while(j < n && arr[j].y == arr[i].y) {
			int k = j;
			while(k < n && arr[k].y == arr[j].y && (k==j || arr[k].x - arr[k-1].x <= arr[k].e))
				k++;
			range.push_back({j,k - 1});
			j = k;
		}

		for(pair<int,int> rng : range) {
			int st = rng.first;
			int en = rng.second;
			LL maks = 0;
			LL sum = 0;
			for(int it = st ; it <= en ; it++) {
				int x = arr[it].x;
				int e = arr[it].e;
				int y = arr[it].y;

				int kiri = max(0,x - e);
				int kanan = min(MAXX,x + e);
				int bawah = y - e;

				sum += arr[it].s;
				LL haha = query(1,0,MAXX,kiri,kanan,bawah);
				maks = max(maks,haha);
				//printf("query %d %d %d ret %lld\n",kiri,kanan,bawah,haha);
			}

			for(int it = st ; it <= en ; it++) {
				dp[it] = sum + maks;
				update(1,0,MAXX,arr[it].x,arr[it].x,arr[it].y,dp[it]);
			}
		}

		/*for(int it = i ; it < j ; it++) {
			int x = arr[it].x;
			int y = arr[it].y;
			//printf("GATE %d %d %d %d stat %lld\n",x,y,arr[i].s,arr[i].e,dp[it]);
			update(1,0,MAXX,x,x,y,dp[it]);
		}*/

		i = j;
	}

	LL ans = 0;
	for(int i = 0 ; i < n ; i++)
		ans = max(ans,dp[i]);
	cout << ans << endl;
	return 0;
}