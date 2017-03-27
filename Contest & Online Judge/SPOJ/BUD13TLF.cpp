#include <bits/stdc++.h>
using namespace std;

const int N = 101;
const int W = 1001;
const int MOD = 10007;

typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back

int dp[N][N][W];
int fact[MOD], inve[MOD];

int cnt[W];
vector<pii> v;
int n,w;

int modPow(int base,int pwr) {
	int res = 1;
	
	while(pwr) {
		if(pwr & 1) res = (res * base) % MOD;
		base = (base * base) % MOD;
		pwr >>= 1;
	}
	
	return res;
}

void precompute() {
	fact[0] = inve[0] = 1;
	
	for(int i = 1 ; i < MOD ; i++) {
		fact[i] = (fact[i - 1] * i) % MOD;
		inve[i] = modPow(fact[i],MOD - 2);
	}
}

int solve(int idx,int use,int sisa) {
	if(idx == v.size()) {
		if(sisa == 0) 	return fact[use];
		else			return 0;
	}
	
	int &ret = dp[idx][use][sisa];
	if(ret != -1) return ret;
	
	ret = 0;
	for(int i = 0 ; i <= v[idx].se && sisa >= i * v[idx].fi ; i++) {
		ret = (ret + inve[i] * solve(idx + 1,use + i,sisa - i * v[idx].fi)) % MOD;
	}
	
	return ret;
}

void resetDPTable() {
	for(int i = 0 ; i < v.size() ; i++)
		for(int j = 0 ; j <= n ; j++)
			for(int k = 0 ; k <= w ; k++)
				dp[i][j][k] = -1;
}

int calculateAll() {
	resetDPTable();
	
	int accumulatedUsage = 0;
	int boxUsed = 0;
	int mulOfInve = 1;
	int res = 0;
	
	for(int i = 0 ; i < v.size() ; i++) {
		for(int j = 0 ; j < v[i].se ; j++) {
			int tot = accumulatedUsage + j * v[i].fi;
			int boxes = boxUsed + j;
			int multiply = (mulOfInve * inve[j]) % MOD;
			
			for(int rem = 0 ; rem <= w ; rem++) {
				if(rem + tot <= w && w - (rem + tot) < v[i].fi) {
					res = (res + multiply * solve(i + 1,boxes,rem)) % MOD;
				}
			}
		}
		
		accumulatedUsage += v[i].se * v[i].fi;
		boxUsed += v[i].se;
		mulOfInve = (mulOfInve * inve[v[i].se]) % MOD;
	}
	
	if(accumulatedUsage <= w) {
		res = (res + mulOfInve * fact[boxUsed]) % MOD;
	}
	
	return res;	
}

void init() {
	scanf("%d %d",&n,&w);
	memset(cnt,0,sizeof cnt);
	
	for(int i = 0 ; i < n ; i++) {
		int x;
		scanf("%d",&x);
		cnt[x]++;
	}
	
	v.clear();
	
	for(int i = 0 ; i < W ; i++) {
		if(cnt[i]) {
			v.pb({i,cnt[i]});
		}
	}
}

int main() {
	precompute();
	int tc;
	scanf("%d",&tc);
	for(int t = 1 ; t <= tc ; t++) {
		init();
		printf("Case %d: %d\n",t,calculateAll());
	}
	return 0;
}