#include <bits/stdc++.h>
using namespace std;

const int MX = 1e4 + 5;
const int L = 210;

struct state {
	int depth;
	int x;
	int way;
	int t;
};

int dist[MX][L][2][2];
bool udah[MX][L][2][2];
int arr[MX][L];
int l, n;

void read() {
	scanf("%d %d",&l,&n);
	for(int i = 0 ; i < n ; i++) {
		int y, x;
		scanf("%d %d",&y,&x);
		assert(0 <= x && x <= l-1);
		assert(1 <= y && y <= 10000);
		arr[y][++x] = 1;
	}
	int y, x;
	scanf("%d %d",&y,&x);
	assert(0 <= x && x <= l-1);
	assert(1 <= y && y <= 10000);
	arr[y][++x] = 2;
}

int solve() {
	deque<state> q;
	for(int i = 0 ; i < MX ; i++)
		for(int j = 0 ; j < L ; j++)
			for(int k = 0 ; k < 2 ; k++)
				for(int l = 0 ; l < 2 ; l++)
					dist[i][j][k][l] = 1e9;

	for(int i = 1 ; i <= l ; i++) {
		dist[0][i][0][0] = 0;
		q.push_front((state){0, i, 0, 0});
	}

	while(!q.empty()) {
		state now = q.front();
		q.pop_front();
		if(udah[now.depth][now.x][now.way][now.t]) {
			continue;
		}
		udah[now.depth][now.x][now.way][now.t] = 1;
		int cur = dist[now.depth][now.x][now.way][now.t];

		if(now.depth+1 == MX) {
			if(now.t == 0) continue;
			return cur;
		}

		//printf("%d %d %d %d\n", now.depth, now.x, now.way, now.t);

		// turun
		if(now.way == 0) {
			if(now.t == 0) {
				if(arr[now.depth][now.x] == 2) {
					continue;
				}
				if(now.x > 1 && arr[now.depth][now.x-1] == 2) {
					if(dist[now.depth][now.x][0][1] > cur) {
						dist[now.depth][now.x][0][1] = cur;
						q.push_front((state){now.depth, now.x, 0, 1});
					}
				}
				if(now.x+1 <= l && arr[now.depth][now.x+1] == 2) {
					if(dist[now.depth][now.x][0][1] > cur) {
						dist[now.depth][now.x][0][1] = cur;
						q.push_front((state){now.depth, now.x, 0, 1});
					}
				}
			}
			if(arr[now.depth+1][now.x] == 1) {
				if(dist[now.depth][now.x][1][now.t] > cur+1) {
					dist[now.depth][now.x][1][now.t] = cur+1;
					q.push_back((state){now.depth, now.x, 1, now.t});
				}
			}
			else if(arr[now.depth+1][now.x] == 0) {
				if(dist[now.depth+1][now.x][0][now.t] > cur) {
					dist[now.depth+1][now.x][0][now.t] = cur;
					q.push_front((state){now.depth+1, now.x, 0, now.t});
				}
			}
		}
		else {
			if(now.t == 0 && arr[now.depth][now.x] == 2) {
				if(dist[now.depth][now.x][1][1] > cur) {
					dist[now.depth][now.x][1][1] = cur;
					q.push_front((state){now.depth, now.x, 1, 1});
				}
			}
			if(now.x > 1 && dist[now.depth][now.x-1][1][now.t] > cur) {
				dist[now.depth][now.x-1][1][now.t] = cur;
				q.push_front((state){now.depth, now.x-1, 1, now.t});
			}
			if(now.x+1 <= l && dist[now.depth][now.x+1][1][now.t] > cur) {
				dist[now.depth][now.x+1][1][now.t] = cur;
				q.push_front((state){now.depth, now.x+1, 1, now.t});
			}
			if(arr[now.depth+1][now.x] != 1 && dist[now.depth+1][now.x][0][now.t] > cur) {
				dist[now.depth+1][now.x][0][now.t] = cur;
				q.push_front((state){now.depth+1, now.x, 0, now.t});
			}
		}
	}

	return -1;
}

int main() {
	read();
	int ret = solve();
	if(ret == -1) {
		puts("Use dynamite");
	}
	else {
		printf("%d\n", ret);
	}
	return 0;
}