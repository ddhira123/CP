#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL INF = 4e18;
const int N = 5e4 + 5;

vector<int> adj[N];
LL w[N];
LL sum[N];
set<LL> s[N];
int ptr[N];
int n;
int cnt;
int r[N];
int urut[N];
map<LL,int> ms;

LL ans;

void dfs(int now,int prv) {
	urut[++cnt] = now;
	sum[now] = w[now];
	for(int nex : adj[now]) {
		if(nex == prv) continue;
		dfs(nex,now);
		sum[now] += sum[nex];
	}
	r[now] = cnt;
}

void solve(int now,int prv) {
	ptr[now] = now;
	for(int nex : adj[now]) {
		if(nex == prv) continue;
		solve(nex,now);
		if(s[ptr[now]].size() > s[ptr[nex]].size()) {
			for(LL x : s[ptr[nex]]) {
				if(s[ptr[now]].count(x)) {
					LL sisa = sum[1] - x - x;
					if(sisa <= x)
						ans = min(ans,x - sisa);
				}
				s[ptr[now]].insert(x);
			}
			s[ptr[nex]].clear();
		}
		else {
			for(LL x : s[ptr[now]]) {
				if(s[ptr[nex]].count(x)) {
					LL sisa = sum[1] - x - x;
					if(sisa <= x)
						ans = min(ans,x - sisa);
				}
				s[ptr[nex]].insert(x);
			}
			s[ptr[now]].clear();
			ptr[now] = ptr[nex];			
		}
	}
	if(sum[now]*2 == sum[1]) {
		ans = min(ans,sum[now]);
	}
	if(now != 1 && sum[now] % 2 == 0 && s[ptr[now]].count(sum[now] / 2)) {
		LL sisa = sum[1] - sum[now];
		if(sisa <= sum[now]/2)
			ans = min(ans,sum[now]/2 - sisa);
	}
	if(now != 1) {
		LL atas = sum[1] - sum[now];
		if(s[ptr[now]].count(atas)) {
			LL sisa = sum[1] - 2*atas;
			if(sisa <= atas)
				ans = min(ans,atas - sisa);
		}
		LL kurang = sum[now] - atas;
		if(s[ptr[now]].count(kurang)) {
			LL sisa = sum[1] - 2*atas;
			if(sisa <= atas)
				ans = min(ans,atas - sisa);
		}
	}
	s[ptr[now]].insert(sum[now]);
}

void corner() {
	for(int i = n ; i >= 1 ; i--) {
		int idx = urut[i];
		//if(idx == 4) cerr << sum[idx] << " woo\n";
		if(ms[sum[idx]] > r[idx]) {
			LL sisa = sum[1] - 2*sum[idx];
			if(sisa <= sum[idx])
				ans = min(ans,sum[idx] - sisa);
		}
		if(ms[sum[1] - 2*sum[idx]] > r[idx]) {
			LL sisa = sum[1] - 2*sum[idx];
			if(sisa <= sum[idx])
				ans = min(ans,sum[idx] - sisa);
		}
		if((sum[1] - sum[idx]) % 2 == 0 && ms[(sum[1] - sum[idx])/2] > r[idx]) {
			//if(idx == 4) cerr << "wo\n";
			LL sama = (sum[1] - sum[idx]) / 2;
			if(sum[idx] <= sama)
				ans = min(ans,sama - sum[idx]);
		}
		ms[sum[idx]] = max(ms[sum[idx]],i);
	}
}

void reset() {
	for(int i = 1 ; i <= n ; i++) {
		s[i].clear();
		adj[i].clear();
	}
	ms.clear();
}

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%lld",w + i);
	for(int i = 1 ; i < n ; i++) {
		int u, v;
		scanf("%d %d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

void work() {
	ans = INF;
	cnt = 0;
	dfs(1,-1);
	solve(1,-1);
	corner();
	if(ans == INF)
		ans = -1;
	printf("%lld\n",ans);
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		work();
		reset();
	}
	return 0;
}