#include <bits/stdc++.h>
using namespace std;

string s[105];
bool vis[105][105];
int n, m;

int dr[4] = {0,-1,0,1};
int dc[4] = {-1,0,1,0};

void dfs(int r,int c) {
	vis[r][c] = 1;
	for(int i = 0 ; i < 4 ; i++) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if(nr >= 0 && nr < n && nc >= 0 && nc < m && !vis[nr][nc] && s[nr][nc] == 'B') {
			dfs(nr,nc);
		}
	}
}

int main() {
	cin >> n >> m;
	for(int i = 0 ; i < n ; i++)
		cin >> s[i];
	int ans = 0;
	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < m ; j++)
			if(s[i][j] == 'B' && !vis[i][j]) {
				ans++;
				dfs(i,j);
			}
	cout << ans << endl;		
	return 0;
}