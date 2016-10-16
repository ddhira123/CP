#include <bits/stdc++.h>
using namespace std;

struct data {
	int tipe;
	long long start;
	int x;
	int y;
};

struct arah {
	int x;
	int y;
	int id;
};

const int N = 1e5 + 5;
const long long INF = 4e18;

vector<data> v;
int n, m, k;
pair<int,int> arr[N];
long long ans[N];

arah getNext(arah cur) {
	arah nxt;

	if(cur.id == 0) {
		int dst = min(n-cur.y,m-cur.x);

		nxt.x = cur.x + dst;
		nxt.y = cur.y + dst;
		if(dst == n-cur.y)
			nxt.id = 1;
		else
			nxt.id = 3;
	}
	else if(cur.id == 1) {
		int dst = min(cur.y,m-cur.x);

		nxt.x = cur.x + dst;
		nxt.y = cur.y - dst;
		if(dst == cur.y)
			nxt.id = 0;
		else
			nxt.id = 2;
	}
	else if(cur.id == 2) {
		int dst = min(cur.y,cur.x);

		nxt.x = cur.x - dst;
		nxt.y = cur.y - dst;
		if(dst == cur.y)
			nxt.id = 3;
		else
			nxt.id = 1;
	}
	else if(cur.id == 3) {
		int dst = min(n-cur.y,cur.x);

		nxt.x = cur.x - dst;
		nxt.y = cur.y + dst;
		if(dst == n-cur.y)
			nxt.id = 2;
		else
			nxt.id = 0;
	}

	return nxt;
}

map<int,vector<int>> mv[2];

void solve() {
	for(int i = 1 ; i <= k ; i++) {
		ans[i] = 4e18;
		mv[0][arr[i].first - arr[i].second].push_back(i);
		mv[1][arr[i].first + arr[i].second].push_back(i);
		//printf("haha %d %d %d\n",i,arr[i].first - arr[i].second,arr[i].first + arr[i].second);
	}
	for(data x : v) {
		//printf("%d %lld %d\n",x.tipe,x.start,x.iden);
		if(x.tipe % 2 == 0) 
			for(int it : mv[0][x.x - x.y]) {
				int dst = abs(x.y - arr[it].second);
				ans[it] = min(ans[it],dst + x.start);
			}	
		else
			for(int it : mv[1][x.x+x.y]) {
				int dst = abs(x.x - arr[it].first);
				ans[it] = min(ans[it],dst + x.start);
			}	
	}

	for(int i = 1 ; i <= k ; i++) {
		if(ans[i] == INF) ans[i] = -1;
		printf("%lld\n",ans[i]);
	} 
}

int main() {
	scanf("%d %d %d",&n,&m,&k);
	swap(n,m);

	for(int i = 1 ; i <= k ; i++)
		scanf("%d %d",&arr[i].first,&arr[i].second);

	arah cur = (arah){0,0,0};
	long long waktu = 0;
	while(1) {
		data dat;
		if(cur.id % 2 == 0)
			dat = (data){cur.id,waktu,cur.x,cur.y};
		else 
			dat = (data){cur.id,waktu,cur.x,cur.y};

		v.push_back(dat);
		//printf("%d %d %d\n",cur.id,cur.x,cur.y);
		arah nxt = getNext(cur);
		waktu += abs(nxt.x - cur.x);
		cur = nxt;

		if(cur.x == 0 && cur.y == 0) break;
		if(cur.x == m && cur.y == 0) break;
		if(cur.x == 0 && cur.y == n) break;
		if(cur.x == m && cur.y == n) break;
		
	}

	solve();
	return 0;
}