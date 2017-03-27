#include <bits/stdc++.h>
using namespace std;

const int N = 6;
const int M = 151;
const int MAXX = 150 * 150 * 150;
const int MOD = 5864401;


int k[N];
int p[N];
int n,m;
vector<pair<int,int> > v[2];

int ans;
int pangkat[M][32];

int last[MOD];
int nex[MAXX];
int cnt[MAXX];
int isi[MAXX];
int saiz;

void pre() {
	for(int i = 2 ; i < M ; i++) {
		pangkat[i][0] = 1;
		for(int j = 1 ; j < 32 ; j++) {
			pangkat[i][j] = pangkat[i][j - 1] * i;
			//cout << i << " " << j << " " << pangkat[i][j] << endl;
		}
	}
	memset(last,-1,sizeof last);
}

int getPower(int x,int pwr) {
	int sign = 1;
	if(x < 0 && pwr % 2 == 1) sign = -1;
	if(abs(x) == 1) return sign;
	return pangkat[abs(x)][pwr] * sign;
}


void read() {
	scanf("%d %d",&n,&m);
	for(int i = 0 ; i < n ; i++)
		scanf("%d %d",k + i,p + i);
}

void make(int now,int sum) {
	if(now == v[1].size()) {
		isi[saiz++] = sum;
	}
	else {
		int kk = v[1][now].first;
		int pp = v[1][now].second;
		for(int i = 1 ; i <= m ; i++)
			make(now + 1,sum + kk * getPower(i,pp));
	}
}

void build_hash_table() {
	for(int i = 0 ; i < saiz ; i++) {
		cnt[i] = 0;
		int val = isi[i] % MOD;
		if(val < 0) val += MOD;

		int cur = last[val];
		while(cur != -1 && isi[cur] != isi[i]) cur = nex[cur];
		if(cur != -1) {
			cnt[cur]++;
		}
		else {
			nex[i] = last[val];
			last[val] = i;
			cnt[i] = 1;
		}
	}
}

void reset() {
	for(int i = 0 ; i < saiz ; i++) {
		int val = isi[i] % MOD;
		if(val < 0) val += MOD;
		last[val] = -1;
	}
}

int getVal(int x) {
	int mod = x % MOD;
	if(mod < 0) mod += MOD;

	int cur = last[mod];
	while(cur != -1 && isi[cur] != x) cur = nex[cur];

	return cur == -1 ? 0 : cnt[cur];
}

void dfs(int now,int sum) {
	if(now == v[0].size()) {
		ans += getVal(-sum);
	}
	else {
		int kk = v[0][now].first;
		int pp = v[0][now].second;
		for(int i = 1 ; i <= m ; i++)
			dfs(now + 1,sum + kk * getPower(i,pp));
	}
}

int solve() {
	reset();
	ans = 0;
	v[0].clear(); v[1].clear();
	saiz = 0;

	for(int i = 0 ; i < n / 2 ; i++)
		v[0].push_back({k[i],p[i]});
	for(int i = n / 2 ; i < n ; i++)
		v[1].push_back({k[i],p[i]});

	make(0,0);
	build_hash_table();
	dfs(0,0);

	return ans;
}

int main() {
	pre();
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		printf("%d\n",solve());
	}
	return 0;
}