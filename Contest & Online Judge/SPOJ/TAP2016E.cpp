#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

bool vis[N][N];
vector<int> radj[N][N];
int n, m;

bool init() {
	if(scanf("%d %d",&n,&m) != 2) return 0;
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= m ; j++) {
			int x; scanf("%d",&x);
			radj[j][x].push_back(i);
		}
	return 1;
}

bool solve() {
	vis[1][1] = 1;
	queue<pair<int,int>> q;
	q.push({1,1});

	while(!q.empty()) {
		pair<int,int> now = q.front();
		q.pop();

		for(int color = 1 ; color <= m ; color++)
			for(int x : radj[color][now.first])
				for(int y : radj[color][now.second])
					if(!vis[x][y]) {
						vis[x][y] = 1;
						q.push({x,y});
					}
	}

	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n ; j++)
			if(!vis[i][j])
				return 0;

	return 1;		
}

void reset() {
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n ; j++)
			vis[i][j] = 0;
	for(int i = 1 ; i <= m ; i++)
		for(int j = 1 ; j <= n ; j++)
			radj[i][j].clear();
		
}

int main() {
	while(init()) {
		printf("%c\n", solve() ? 'S' : 'N');
		reset();
	}
	return 0;
}