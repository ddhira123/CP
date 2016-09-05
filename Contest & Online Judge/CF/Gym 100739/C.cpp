#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

int dr[4] = {1,0,-1,0};
int dc[4] = {0,1,0,-1};

struct robot {
	int r;
	int c;
	int ways;
};

const int N = 205;

int dist[N][N][4];
int n;
string str[N];

int main() {
	memset(dist,-1,sizeof dist);
	cin >> n;
	for(int i = 0 ; i < n ; i++)
		cin >> str[i];

	dist[0][0][0] = 0;
	queue<robot> q;
	q.push((robot){0,0,0});
	while(!q.empty()) {
		robot now = q.front();
		q.pop();
		if(dist[now.r][now.c][(now.ways + 1) % 4] == -1) {
			dist[now.r][now.c][(now.ways + 1) % 4] = dist[now.r][now.c][now.ways] + 1;
			q.push((robot){now.r,now.c,(now.ways + 1) % 4});
		}
		int ways = now.ways;
		int nr = now.r + dr[ways];
		int nc = now.c + dc[ways];
		if(nr >= 0 && nr < n && nc >= 0 && nc < n && str[nr][nc] == '.' && dist[nr][nc][ways] == -1) {
			dist[nr][nc][ways] = dist[now.r][now.c][now.ways] + 1;
			q.push((robot){nr,nc,ways});
		} 
	}
	printf("%d\n",dist[n-1][n-1][0]);
	return 0;
}