/**
	Prim's

	O(V^2) implementation. No need for any complicated data structures / algo.
	Faster in dense graph.
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 1000 + 5;
const int INF = 1e9;

// store cost in matrix
int cost[N][N];
int minDist[N];
bool taken[N];
int n;

long long primQuadratic() {
	// set taken[] to false and minDist[] to INF ..
	for(int i = 1 ; i <= n ; i++) {
		minDist[i] = INF;
		taken[i] = 0;
	}
	// .. except first vertice
	minDist[1] = 0;

	long long ans = 0;
	for(int i = 0 ; i < n ; i++) {
		int best = INF;
		int idx = -1;

		// search for lowest minDist[]
		// lowest minDist[] stored in best, while index stored in idx
		for(int j = 1 ; j <= n ; j++) {
			// found lower minDist[] that hasn't been taken
			if(!taken[j] && minDist[j] <= best) {
				best = minDist[j];
				idx = j;
			}
		}

		if(best == INF) {
			break;
		}

		ans += best;
		taken[idx] = 1;

		// update minDist[]; expand from idx
		for(int j = 1 ; j <= n ; j++) {
			minDist[j] = min(minDist[j],cost[idx][j]);
		}
	}

	return ans;
}

int main() {
	return 0;
}