#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second

const int N = 401;
const int MX = 2*N;
const int INF = 1e9;

int dist[2][N][N];
int dr[4] = {-1,0,1,0};
int dc[4] = {0,-1,0,1};
int L[N][N], R[N][N];
int n, m, r1, c1, r2, c2;

void relax(int dis,int rr,int cc) {
	int ndis = dis-1;

	for(int i = 0 ; i < 4 ; i++) {
		int nr = rr + dr[i];
		int nc = cc + dc[i];
		if(nr >= 1 && nr <= n && nc >= 1 && nc <= m) {
			if(dist[ndis & 1][nr][nc] == -1)
				dist[ndis & 1][nr][nc] = dist[dis & 1][rr][cc]+1;
			else
				dist[ndis & 1][nr][nc] = min(dist[ndis & 1][nr][nc], dist[dis & 1][rr][cc] + 1);
		}
	}
}

int solve() {
	memset(dist,-1,sizeof dist);
	int ans = INF;
	for(int i = R[r1][c1] ; i >= 1 ; i--) {
		int bit = i & 1;
		int nbit = bit ^ 1;
		memset(dist[nbit],-1,sizeof dist[nbit]);
		if(L[r1][c1] <= i) dist[bit][r1][c1] = 0;
		if(dist[bit][r2][c2] != -1 && L[r2][c2] <= i && i <= R[r2][c2]) ans = min(ans,dist[bit][r2][c2]);

		for(int j = 1 ; j <= n ; j++)
			for(int k = 1 ; k <= m ; k++)
				if(dist[bit][j][k] != -1) {
					//cout << i << " " << j << " " << k << " " << dist[bit][j][k] << "\n";
					relax(i,j,k);
				}
	}
	if(ans == INF) ans = -1;
	return ans;
}

void read() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	cin >> n >> m >> r1 >> c1 >> r2 >> c2;
	r1++; c1++; r2++; c2++;
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= m ; j++)
			cin >> L[i][j];
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= m ; j++)
			cin >> R[i][j];
}

int main() {
	read();
	cout << solve() << "\n";
	return 0;
}