#include <bits/stdc++.h>
using namespace std;

const int N = 40;
const int K = 20;
const int MOD = 10007;
const int MAGIC = 9885;

vector<long long> all;
int dp[N + 1][K + 1][K + 1][K + 1][2][3];
int C[N + 1][K + 1];
int helper[MAGIC][K + 1];

int n,k;
char s[2][N + 5];
int need[N + 5];
int exactly[K + 5];

void init() {
	memset(C,-1,sizeof C);
	memset(helper,-1,sizeof helper);

	for(int i = 0 ; i < N ; i++)
		for(int j = i + 1 ; j < N ; j++)
			for(int l = j + 1 ; l < N ; l++) {
				all.push_back((1LL << i) | (1LL << j) | (1LL << l));
				assert(__builtin_popcountll(all.back()) == 3);
			}

	sort(all.begin(),all.end());		
}

bool read() {
	if(scanf("%d %d",&n,&k) != 2) return 0;
	if((n | k) == 0) return 0;

	for(int i = 0 ; i < 2 ; i++)
		scanf("%s",s[i]);

	for(int i = 0 ; i < n ; i++)
		need[i] = (s[0][i] - '0') ^ (s[1][i] - '0');
}

int comb(int x,int y) {
	if(x < y) return 0;
	if(y == 0) return 1;

	int &ret = C[x][y];
	if(ret != -1) return ret;

	ret = comb(x - 1,y) + comb(x - 1,y - 1);
	if(ret >= MOD) ret -= MOD;

	return ret;
}

int helperDP(int idx,int need) {
	if(need == 0) return 1;
	if(idx == -1) return 0;

	int &ret = helper[idx][need];
	if(ret != -1) return ret;

	ret = helperDP(idx - 1,need) + helperDP(idx,need - 2);
	if(ret >= MOD) ret -= MOD;

	return ret;
}

int solve(int now,int three,int two,int one,int stat,int pos) {
	if(now == n) {
		return three + two + one == 0;
	}
	if(pos == 3) {
		if(stat != need[now]) return 0;
		return solve(now + 1,three,two,one,0,0);
	}

	int &ret = dp[now][three][two][one][stat][pos];
	if(ret != -1) return ret;
	ret = 0;

	if(pos == 0) {
		for(int i = 0 ; i <= one ; i++) {
			ret += solve(now,three,two,one - i,stat ^ (i & 1),pos + 1) * comb(one,i);
			if(ret >= MOD) ret %= MOD;
		}
	}
	else if(pos == 1) {
		for(int i = 0 ; i <= two ; i++) {
			ret += solve(now,three,two - i,one + i,stat ^ (i & 1),pos + 1) * comb(two,i);
			if(ret >= MOD) ret %= MOD;
		}		
	}
	else {
		for(int i = 0 ; i <= three ; i++) {
			ret += solve(now,three - i,two + i,one,stat ^ (i & 1),pos + 1) * comb(three,i);
			if(ret >= MOD) ret %= MOD;
		}		
	}

	return ret;
}

int rec(int now,int kk,long long x) {
	if(kk == 0) return x == 0;
	if(now == -1) return 0;
	return rec(now - 1,kk,x) + rec(now - 1,kk - 1,x ^ all[now]);
}

void test(int en) {
	long long tgt = 0;
	for(int i = 0 ; i < n ; i++)
		if(need[i]) tgt |= (1 << i);

	printf("%d\n",rec(en,k,tgt));
}

int solveProblem() {
	memset(dp,-1,sizeof dp);
	int en = lower_bound(all.begin(),all.end(),1LL << n) - all.begin();
	en--;
	test(en);

	for(int i = 0 ; i <= k ; i++) {
		exactly[i] = solve(0,i,0,0,0,0);
		printf("%d : %d\n",i,exactly[i]);
		for(int j = i - 2 ; j >= 0 ; j -= 2) {
			exactly[i] -= exactly[j] * helperDP(en,i - j);
			exactly[i] %= MOD;
		}
		if(exactly[i] < 0) exactly[i] += MOD;
	}

	return exactly[k];
}


int main() {
	init();
	int tc = 0;
	while(read()) {
		printf("Case %d: %d\n",++tc,solveProblem());
	}
	return 0;
}