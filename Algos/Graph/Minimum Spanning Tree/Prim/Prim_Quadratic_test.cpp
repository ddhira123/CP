// SPOJ - DAVIDG
#include <bits/stdc++.h>
using namespace std;

const int N = 1000 + 5;
const int INF = 1e9;
const int MOD = 1e9 + 7;

// cost[i][j] is distance(i,j)^2
int cost[N][N];
int minDist[N];
bool taken[N];
int x[N], y[N];
int n, p;

int primQuadratic() {
	for(int i = 1 ; i <= n ; i++) {
		minDist[i] = INF;
		taken[i] = 0;
	}
	minDist[1] = 0;

	long long ans = 0;
	for(int i = 0 ; i < n ; i++) {
		int best = INF;
		int idx = -1;

		for(int j = 1 ; j <= n ; j++) {
			if(!taken[j] && minDist[j] <= best) {
				best = minDist[j];
				idx = j;
			}
		}

		if(best == INF) {
			break;
			best = 0;
		}

		ans += (long long)ceil(sqrt(best)*p);
		taken[idx] = 1;

		for(int j = 1 ; j <= n ; j++) {
			minDist[j] = min(minDist[j],cost[idx][j]);
		}
	}

	return ans % MOD;
}

int sqr(int a) {
	return a*a;
}

void read() {
	scanf("%d %d",&n,&p);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d %d",x + i,y + i);
	}
}

void makeCost() {
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n ; j++) {
			cost[i][j] = sqr(x[i] - x[j]) + sqr(y[i] - y[j]);
		}
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		makeCost();
		printf("Scenario #%d: %d\n",tc,primQuadratic());
	}
	return 0;
}