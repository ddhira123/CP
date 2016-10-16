#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const long long INFLL = 4e18;

vector<int> adj[N];
vector<int> seen;
int val[N];
int n;
int a[N], b[N];

pair<int,int> best[N][2];

void upd(int x,pair<int,int> temp) {
	if(best[x][1] < temp) best[x][1] = temp;
	if(best[x][0] < best[x][1]) swap(best[x][0],best[x][1]);
}

void dfs1(int now,int prv) {
	best[now][0] = best[now][1] = {1,now};
	for(int nex : adj[now]) {
		if(nex == prv) continue;
		dfs1(nex,now);
		upd(now,{best[nex][0].first+1,nex});
	}
}

void dfs2(int now,int prv) {
	for(int nex : adj[now]) {
		if(nex == prv) continue;
		for(int i = 0 ; i < 2 ; i++)
			if(best[now][i].second != nex) {
				upd(nex,{best[now][i].first+1,now});
				break;
			}
		dfs2(nex,now);	
	}
}

void read() {
	scanf("%d",&n);
	for(int i = 0 ; i+1 < n ; i++)
		scanf("%d %d",a + i,b + i);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",val + i);
}

void init() {
	for(int i = 0; i+1 < n ; i++)
		if(val[a[i]] == 1 && val[b[i]] == 1) {
			adj[a[i]].push_back(b[i]);
			adj[b[i]].push_back(a[i]);
		}
}

void updAns(long long &a,long long &b,long long c,long long d) {
	if(a == INFLL || a*d > b*c) {
		a = c;
		b = d;
	}
}

void solve() {
	for(int i = 1 ; i <= n ; i++) {
		if(best[i][0].first != 0 || val[i] != 1) continue;
		dfs1(i,i);
		dfs2(i,i);
	}
	for(int i = 1 ; i <= n ; i++) {
		adj[i].clear();
		//printf("%d -> %d %d %d %d\n",i,best[i][0].first,best[i][0].second,best[i][1].first,best[i][1].second);
	}
	for(int i = 0 ; i+1 < n ; i++) {
		adj[a[i]].push_back(b[i]);
		adj[b[i]].push_back(a[i]);
	}

	long long a = INFLL;
	long long b = 1;

	int mx = -1;
	for(int i = 1 ; i <= n ; i++) mx = max(mx,best[i][0].first);
	if(mx > 0) {
		updAns(a,b,1,mx);
	}
	for(int i = 1 ; i <= n ; i++)
		if(val[i] != 1) {
			vector<int> v;
			for(int x : adj[i])
				if(val[x] == 1)
					v.push_back(best[x][0].first);
			int bawah = 1;
			if(v.size() > 0) bawah += v[0];
			if(v.size() > 1) bawah += v[1];
			updAns(a,b,val[i],bawah);	
		}
	int fpb = __gcd(a,b);
	a /= fpb;
	b /= fpb;
	printf("%lld/%lld\n",a,b);		
}

int main() {
	read();
	init();
	solve();	
	return 0;
}