#include <bits/stdc++.h>
using namespace std;

const int N = 205;
const int MOD = 1e9 + 7;

int mat[N][N];
int n, m;
int dp[N][10];

int C(int a,int b) {
	if(b > a) return 0;
	if(a < 0 || b < 0) return 0;
	if(b == 0) return 1;
	int &ret = dp[a][b];
	if(ret != -1) return ret;
	ret = (C(a-1,b) + C(a-1,b-1)) % MOD;
	return ret;
}

int main() {
	memset(dp,-1,sizeof dp);
	cin >> n >> m;
	for(int i = 0 ; i < m ; i++) {
		int u, v;
		cin >> u >> v;
		mat[u][v] = mat[v][u] = 1;
	}

	int ans = 0;
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n ; j++)
			if(i != j && mat[i][j]) {
				// i anak 3
				// j anak 2
				int onlyI = 0;
				int onlyJ = 0;
				int both = 0;

				for(int k = 1 ; k <= n ; k++)
					if(mat[i][k] && mat[j][k])
						both++;
					else if(mat[i][k] && k != j)
						onlyI++;
					else if(mat[j][k] && k != i)
						onlyJ++;

				for(int bothI = 0 ; bothI <= 3 ; bothI++)
					for(int bothJ = 0 ; bothJ <= 2 ; bothJ++) {
						int dual = bothJ + bothI;
						int soloI = 3 - bothI;
						int soloJ = 2 - bothJ;

						int add = 1ll * C(both,bothI) * C(both-bothI,bothJ) % MOD;
						add = 1ll * add * C(onlyI,soloI) % MOD;
						add = 1ll * add * C(onlyJ,soloJ) % MOD;
						ans = (ans + add) % MOD;
					}
				//cout << i << " " << j << " " << lol << "\n";	
			}

	cout << ans << "\n";
	return 0;
}