#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int n, m;
char s[N][N];
int num[N][N];
vector<pair<int,int>> bomb;
vector<pair<int,int>> important;
int cntr;

void fail() {
	puts("INVALID");
	exit(0);
}

void valid() {
	puts("VALID");
	exit(0);
}

void read() {
	scanf("%d %d", &n, &m);
	for(int i = 0 ; i < n ; i++) {
		scanf("%s", s[i]);
	}
}

void init() {
	for(int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j < m ; j++)
			if(s[i][j] == '?') {
				bomb.push_back({i, j});
				num[i][j] = cntr++;
			} else {
				num[i][j] = -1;
			}
	}
	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < m ; j++) {
			if(s[i][j] == '*' || s[i][j] == '?') continue;

			bool ada = 0;
			for(int k = 0 ; k < 8 ; k++) {
				int nr = i + dr[k];
				int nc = j + dc[k];

				if(nr >= 0 && nr < n && nc >= 0 && nc < m && num[nr][nc] != -1) {
					important.push_back({i, j});
					ada = true;
					break;
				}
			}

			if(!ada) {
				int need = s[i][j] - '0';
				for(int k = 0 ; k < 8 ; k++) {
					int nr = i + dr[k];
					int nc = j + dc[k];

					if(nr >= 0 && nr < n && nc >= 0 && nc < m && s[nr][nc] == '*') {
						need--;
					}
				}

				if(need != 0) {
					fail();
				}
			}
		}
}

void solve() {
	int sz = bomb.size();
	for(int i = 0 ; i < (1 << sz) ; i++) {
		for(int j = 0 ; j < sz ; j++) {
			int r = bomb[j].first;
			int c = bomb[j].second;

			if(i & (1 << j)) {
				s[r][c] = '*';
			} else {
				s[r][c] = '?';
			}
		}

		bool can = true;

		for(auto it : important) {
			int r = it.first;
			int c = it.second;
			int need = s[r][c] - '0';

			for(int k = 0 ; k < 8 ; k++) {
				int nr = r + dr[k];
				int nc = c + dc[k];

				if(nr >= 0 && nr < n && nc >= 0 && nc < m && s[nr][nc] == '*') {
					need--;
				}
			}

			if(need != 0) {
				can = false;
				break;
			}
		}

		// printf("%d\n", i);

		if(can) {
			valid();
		}
	}

	fail();
}

int main() {
	read();
	init();
	solve();
	return 0;
}