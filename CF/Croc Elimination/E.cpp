#include <bits/stdc++.h>
using namespace std;

const int MOD = (int)1e9 + 7;

typedef pair<int,int> pii;
#define fi first
#define se second;

int nex[1000005][26];
char s[1000005];
int dp[2000005];
int tampung[26];
int n,k;
int m;

pii urut[26];

inline void add(int &x,int y) {
	x += y;
	if(x >= MOD) x -= MOD;
}

int main() {
	scanf("%d %d",&n,&k);
	scanf("%s",s);
	m = strlen(s);

	for(int i = 0 ; i < k ; i++)
		nex[m][i] = -1;
	for(int i = m - 1 ; i >= 0 ; i--) {
		for(int j = 0 ; j < k ; j++)
			nex[i][j] = nex[i + 1][j];
		nex[i][s[i] - 'a'] = i + 1;
	}
	dp[0] = 1;
	int ans = 0;
	for(int i = 0 ; i <= m ; i++) {
		add(ans,dp[i]);
		//printf("%d\n",dp[i]);
		for(int j = 0 ; j < k ; j++) {
			int nxt = nex[i][j];
			if(nxt == -1)
				add(tampung[j],dp[i]);
			else
				add(dp[nxt],dp[i]);
		}
	}

	for(int i = 0 ; i < k ; i++)
		urut[i] = {-1,i};
	for(int i = 0 ; i < m ; i++)
		urut[s[i] - 'a'].fi = i;

	sort(urut,urut + k);

	for(int i = 0 ; i < n ; i++) {
		int cur = i % k;
		int idx = urut[cur].se;
		int lel = tampung[idx];

		add(ans,lel);
		for(int j = 0 ; j < k ; j++)
			add(tampung[j],lel);

		tampung[idx] = lel;
	}

	printf("%d\n",ans);
	return 0;
}