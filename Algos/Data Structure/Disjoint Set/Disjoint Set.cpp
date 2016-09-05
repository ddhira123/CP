/**
	Disjoint Set

	Data structure to represent "group"
	Here i will use compact DSU, where pset[root] represents size of the "group" multiplied by -1

	Complexity : should be O(N log N) because I don't use rank
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int pset[N];

// initialize
void init() {
	// in the beginning, all "group" has size 1
	for(int i = 0 ; i < N ; i++)
		pset[i] = -1;
}

// find root of the "group"
int finds(int x) {
	// pset[x] will be negative if and only if x is root
	return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

// check whether u and v is in the same "group"
bool same(int u,int v) {
	return finds(u) == finds(v);
}

void join(int u,int v) {
	// stop if they are already in the same "group"
	if(same(u,v)) return;

	u = finds(u);
	v = finds(v);

	// set u as v's new root
	pset[u] += pset[v];
	pset[v] = u;
}

int main() {
	return 0;
}