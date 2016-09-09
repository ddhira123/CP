/**
	Prim's

	This one used priority_queue, hence it runs in O((E+V) log E)
	In sparse graph, faster then O(V^2) implementation
*/
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second

const int N = 1e5 + 5;
const int M = 1e5 + 5;
const int INF = 1e9;

// store edge as <next,cost>
vector<pii> adj[N];
bool taken[N];
int n;

long long primPriorityQueue() {
	// store edge in non-decreasing order
	// pair<cost,vertex>
	priority_queue<pii,vector<pii>,greater<pii>> pq;

	// if we change i <= 1 to i <= n
	// then we will have minimum spanning forest instead
	for(int i = 1 ; i <= 1 ; i++) {
		pq.push({INF,i});
	}

	long long ans = 0;
	while(!pq.empty()) {
		pii now = pq.top();
		pq.pop();

		// already processed; skip
		if(taken[now.se]) continue;
		// dummy edge, marking new component
		// hence, change it to 0
		if(now.fi == INF) now.fi = 0;

		taken[now.se] = 1;
		ans += now.fi;

		// expand
		for(pii nex : adj[now.se]) {
			pq.push({nex.se,nex.fi});
		}
	}

	return ans;
}

int main() {
	return 0;
}