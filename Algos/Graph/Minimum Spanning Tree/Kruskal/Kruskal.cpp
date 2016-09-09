/**
	Kruskal's 

	One of popular algo to find Minimum Spanning Tree and its variant
	Main observation is that, there is no cycle in tree
	Hence, we can track each component, and gradually add edge as long they won't make any cycle
	How? Use Disjoint Set
	In what order do we add edges? Non-decreasing, since we want to minimize total cost
	Hence, it's O(E log E) for sorting edges 
*/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 1e5 + 5;

// coz writing pair<int,pair<int,int>> is a bit ugly
// though i do it sometimes...
struct edge {
	int u;
	int v;
	int cost;

	bool operator <(edge other) const {
		return cost < other.cost;
	}
};

int pset[N];
vector<edge> arr;

// usual DSU routine
void init() {
	memset(pset,-1,sizeof pset);
}

int finds(int x) {
	return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

bool same(int u,int v) {
	return finds(u) == finds(v);
}

void join(int u,int v) {
	if(same(u,v)) return;
	u = finds(u);
	v = finds(v);
	pset[u] += pset[v];
	pset[v] = u;
}
//

long long kruskal() {
	init();
	sort(arr.begin(),arr.end());

	long long ans = 0;
	for(edge x : arr) {
		int u = x.u;
		int v = x.v;

		// suppose we add this edge
		// we won't have cycle, since u and v are not in the same component
		// hence, greedily, we add this edge to MST
		if(!same(u,v)) {
			join(u,v);
			ans += x.cost;
		}
	}

	return ans;
}

int main() {
	return 0;
}