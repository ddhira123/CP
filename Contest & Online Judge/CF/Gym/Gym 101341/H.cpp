#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;

int arr[N][N];
int pmax[4][N][N];
int n, m;

void read() {
	scanf("%d %d", &n, &m);
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= m ; j++)
			scanf("%d", &arr[i][j]);
}

void precompute() {
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= m ; j++) {
			pmax[0][i][j] = arr[i][j];
			pmax[0][i][j] = max(pmax[0][i][j], pmax[0][i][j-1]);
			pmax[0][i][j] = max(pmax[0][i][j], pmax[0][i-1][j]);
		}

	for(int i = 1 ; i <= n ; i++)
		for(int j = m ; j >= 1 ; j--) {
			pmax[1][i][j] = arr[i][j];
			pmax[1][i][j] = max(pmax[1][i][j], pmax[1][i][j+1]);
			pmax[1][i][j] = max(pmax[1][i][j], pmax[1][i-1][j]);
		}

	for(int i = n ; i >= 1 ; i--)
		for(int j = 1 ; j <= m ; j++) {
			pmax[2][i][j] = arr[i][j];
			pmax[2][i][j] = max(pmax[2][i][j], pmax[2][i][j-1]);
			pmax[2][i][j] = max(pmax[2][i][j], pmax[2][i+1][j]);
		}
	
	for(int i = n ; i >= 1 ; i--)
		for(int j = m ; j >= 1 ; j--) {
			pmax[3][i][j] = arr[i][j];
			pmax[3][i][j] = max(pmax[3][i][j], pmax[3][i][j+1]);
			pmax[3][i][j] = max(pmax[3][i][j], pmax[3][i+1][j]);
		}
}

int forbid(int a, int b) {
	int ret = 0;
	ret = max(ret, pmax[0][a-1][b-1]);
	ret = max(ret, pmax[1][a-1][b+1]);
	ret = max(ret, pmax[2][a+1][b-1]);
	ret = max(ret, pmax[3][a+1][b+1]);
	return ret;
}

void solve() {
	int mx = 2e9;
	int rb = -1;
	int cb = -1;

	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= m ; j++) {
			if(forbid(i, j) < mx) {
				mx = forbid(i, j);
				rb = i;
				cb = j;
			}
		}	

	// printf("%d\n", mx);
	printf("%d %d\n", rb, cb);
}

int main() {
	read();
	precompute();
	solve();
	return 0;
}