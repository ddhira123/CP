#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second

const int N = 105;
const int INF = 1e9;

int dr[4] = {-1,0,1,0};
int dc[4] = {0,-1,0,1};

int dist[N][N][16];
string arr[N];
int r, c;

void reset() {
	for(int i = 0 ; i < r ; i++)
		for(int j = 0 ; j < c ; j++)
			for(int k = 0 ; k < 16 ; k++)
				dist[i][j][k] = -1;
}

int BFS() {
	reset();

	int rr = -1, cc = -1;
	for(int i = 0 ; i < r ; i++)
		for(int j = 0 ; j < c ; j++)
			if(arr[i][j] == '*') {
				rr = i;
				cc = j;
			}

	queue<pair<pii,int>> q;
	q.push({{rr,cc},0});
	dist[rr][cc][0] = 0;

	while(!q.empty()) {
		rr = q.front().fi.fi;
		cc = q.front().fi.se;
		int bm = q.front().se;

		q.pop();
		for(int i = 0 ; i < 4 ; i++) {
			int nr = rr + dr[i];
			int nc = cc + dc[i];

			if(nr < 0 || nr >= r || nc < 0 || nc >= c || arr[nr][nc] == '#') continue;
			if(arr[nr][nc] == 'R' && (bm & 1) == 0) continue;
			if(arr[nr][nc] == 'G' && (bm & 2) == 0) continue;
			if(arr[nr][nc] == 'Y' && (bm & 4) == 0) continue;
			if(arr[nr][nc] == 'B' && (bm & 8) == 0) continue;

			int nbm = bm;
			if(arr[nr][nc] == 'r') nbm |= 1;
			if(arr[nr][nc] == 'g') nbm |= 2;
			if(arr[nr][nc] == 'y') nbm |= 4;
			if(arr[nr][nc] == 'b') nbm |= 8;

			if(dist[nr][nc][nbm] == -1) {
				dist[nr][nc][nbm] = dist[rr][cc][bm]+1;
				q.push({{nr,nc},nbm});
			}
		}
	}

	int ans = INF;
	for(int i = 0 ; i < r ; i++)
		for(int j = 0 ; j < c ; j++)
			if(arr[i][j] == 'X') {
				for(int k = 0 ; k < 16 ; k++)
					ans = min(ans,dist[i][j][k] == -1 ? INF : dist[i][j][k]);
			}

	return ans;		
}

int main() {
	cin >> r >> c;
	while(r+c > 0) {
		for(int i = 0 ; i < r ; i++)
			cin >> arr[i];

		int ret = BFS();
		if(ret < INF)
			printf("Escape possible in %d steps.\n",ret);
		else
			puts("The poor student is trapped!\n");
		cin >> r >> c;
	}
	return 0;
}