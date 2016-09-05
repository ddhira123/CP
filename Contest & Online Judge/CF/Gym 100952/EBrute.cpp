#include <bits/stdc++.h>
using namespace std;

int dr[4] = {0,1,0,-1};
int dc[4] = {-1,0,1,0};
int mat[15][15];
int arr[15][15];
int n, m, k, p;

bool check(int r,int c,int x) {
	if(arr[r][c] != 0) return 0;
	for(int i = 0 ; i < 4 ; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if(nr >= 0 && nr < n && nc >= 0 && nc < m) {
			if(mat[x][arr[nr][nc]]) return 0;
		}
	}
	return 1;
}

int rec(int dpt) {
	if(dpt > k) return 1;
	int ret = 0;
	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < m ; j++)
			if(check(i,j,dpt)) {
				arr[i][j] = dpt;
				ret += rec(dpt+1);
				arr[i][j] = 0;
			}
	return ret;		
}

void read() {
	cin >> n >> m >> k;
	cin >> p;
	memset(mat,0,sizeof mat);
	for(int i = 0 ; i < p ; i++) {
		int a, b;
		cin >> a >> b;
		mat[a][b] = mat[b][a] = 1;
	}
}

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		int ret = rec(1);
		if(ret) cout << ret << "\n";
		else cout << "impossible\n";
	}
	return 0;
}