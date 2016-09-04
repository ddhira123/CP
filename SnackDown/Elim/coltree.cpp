#include <bits/stdc++.h>
using namespace std;

const int N = 51;
const long long MOD = 1e9 + 7;

long long modpow(long long base,int po) {
	long long ret = 1;
	while(po) {
		if(po & 1) ret = (ret * base) % MOD;
		base = (base * base) % MOD;
		po >>= 1;
	}
	return ret;
}

long long fact[N];
int kiri[N], kanan[N];
int dp[N][N];
vector<int> adj[N];
vector<int> chld[N];
int n, k;

long long P(int a,int b) {
	assert(b <= a);
	return (fact[a] * modpow(fact[a-b],MOD-2)) % MOD;
}

void dfs(int now,int prv) {
	for(int nex : adj[now]) {
		if(nex == prv) continue;
		chld[now].push_back(nex);
		dfs(nex,now);
	}
}

void make() {
	dfs(1,0);

	for(int i = 1 ; i <= n ; i++) {
		if(!chld[i].empty()) kiri[i] = chld[i][0];
		for(int j = 1 ; j < chld[i].size() ; j++)
			kanan[chld[i][j-1]] = chld[i][j];
	}
}

int solve(int cur,int group) {
	if(cur == -1) {
		if(group != 0) return -1;
		return 1;
	}
	if(group < 0) return 0;

	int &ret = dp[cur][group];
	if(ret != -1) return ret;
	ret = 0;

	int right = kanan[cur];
	int left = kiri[cur];

	for(int i = 0 ; i <= group ; i++) {
		long long a, b;
		// kiri, kanan sama kayak sekarang
		a = solve(left,i);
		b = solve(right,group-i);
		if(a == -1 || b == -1) a = 0;
		a = (a * b) % MOD;
		ret = (ret + a) % MOD;
		// kiri sama kanan beda
		if(right != -1) {
			a = solve(left,i);
			b = solve(right,group-i-1);
			if(a == -1 || b == -1) a = 0;
			a = (a * b) % MOD;
			ret = (ret + a) % MOD;
		}
		// kiri beda kanan sama
		if(left != -1) {
			a = solve(left,i-1);
			b = solve(right,group-i);
			if(a == -1 || b == -1) a = 0;
			a = (a * b) % MOD;
			ret = (ret + a) % MOD;
		}
		// kiri sama kanan beda
		if(left != -1 && right != -1) {
			a = solve(left,i-1);
			b = solve(right,group-i-1);
			if(a == -1 || b == -1) a = 0;
			a = (a * b) % MOD;
			ret = (ret + a) % MOD;
		}
	}

	//printf("%d %d %d\n",cur,group,ret);
	return ret;
}

void precompute() {
	fact[0] = 1;
	for(int i = 1 ; i < N ; i++)
		fact[i] = (fact[i-1] * i) % MOD;
}

void reset() {
	memset(dp,-1,sizeof dp);
	memset(kiri,-1,sizeof kiri);
	memset(kanan,-1,sizeof kanan);
	for(int i = 1 ; i <= n ; i++) {
		adj[i].clear();
		chld[i].clear();
	}
}

int main() {
	precompute();

	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		reset();
		scanf("%d %d",&n,&k);

		for(int i = 1 ; i < n ; i++) {
			int u, v;
			scanf("%d %d",&u,&v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		make();
		long long ans = 0;
		for(int i = 1 ; i <= k ; i++) {
			long long ret = solve(1,i-1);
			ret = (ret * P(k,i)) % MOD;
			ans = (ans + ret) % MOD;
		}

		printf("%lld\n",ans);
	}
	return 0;
}