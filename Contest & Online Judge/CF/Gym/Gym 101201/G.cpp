#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

int dr[4] = {-1, 0, 1 ,0};
int dc[4] = {0, 1, 0, -1};

string s[MAXN];
bool udah[MAXN][MAXN];
bool can[MAXN][MAXN];
int r, c;

vector<int> adj[MAXN*MAXN];
int match[MAXN*MAXN];
bool vis[MAXN*MAXN];

int ans;

int getId(int rr, int cc) {
	return rr * c + cc;
}

void dfs(int rr, int cc) {
	if(udah[rr][cc]) {
		return;
	}

	udah[rr][cc] = 1;

	for(int i = 0 ; i < 4 ; i++) {
		int nr = rr + dr[i];
		int nc = cc + dc[i];

		if(nr >= 0 && nr < r && nc >= 0 && nc < c && s[nr][nc] == 'L') {
			dfs(nr, nc);
		}
	}
}

int augment(int now) {
	if(vis[now]) return 0;
	vis[now] = 1;

	for(int nex : adj[now])
		if(match[nex] == -1 || augment(match[nex])) {
			match[nex] = now;
			return 1;
		}

	return 0;
}

int MIS() {
	int active = 0;
	int matched = 0;

	memset(match, -1, sizeof match);
	for(int i = 0 ; i < r ; i++)
		for(int j = 0 ; j < c ; j++)
			if(can[i][j]) {
				active++;

				if((i + j) & 1) {
					memset(vis, 0, sizeof vis);
					matched += augment(getId(i, j));
				}
			}

	return active - matched;
}

void read() {
	cin >> r >> c;
	for(int i = 0 ; i < r ; i++) {
		cin >> s[i];
	}
}

void prepare() {
	for(int i = 0 ; i < r ; i++)
		for(int j = 0 ; j < c ; j++)
			can[i][j] = (s[i][j] == 'C');

	for(int i = 0 ; i < r ; i++)
		for(int j = 0 ; j < c ; j++)
			if(s[i][j] == 'L') {
				if(!udah[i][j]) {
					ans++;
					dfs(i, j);
				}
				for(int k = 0 ; k < 4 ; k++) {
					int ni = i + dr[k];
					int nj = j + dc[k];

					if(ni >= 0 && ni < r && nj >= 0 && nj < c) {
						if(s[ni][nj] == 'C') {
							can[ni][nj] = 0;
						}
					}
				}
			}

	for(int i = 0 ; i < r ; i++)
		for(int j = 0 ; j < c ; j++) 
			if(can[i][j]){
				// cout << i << " " << j << endl;
				if((i + j) % 2 == 1) {
					for(int k = 0 ; k < 4 ; k++) {
						int ni = i + dr[k];
						int nj = j + dc[k];

						if(ni >= 0 && ni < r && nj >= 0 && nj < c) {
							if(can[ni][nj]) {
								adj[getId(i, j)].push_back(getId(ni, nj));	
								// printf("%d %d -> %d %d\n", i, j, ni, nj);
							}
						}
					}
				}
			}
}

int main() {
	read();
	prepare();
	// cout << ans << endl;
	ans += MIS();

	cout << ans << endl;
	return 0;
}