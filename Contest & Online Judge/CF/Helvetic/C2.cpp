#include <bits/stdc++.h>
using namespace std;

int dst[100005];
int n, m;
vector<int> adj[100005];

void dfs(int x) {
	for(int nex : adj[x]) {
		if(dst[nex] != -1) continue;
		dst[nex] = dst[x] + 1;
		dfs(nex);
	}
}

int getFarthest(int x) {
	memset(dst,-1,sizeof dst);
	dst[x] = 0;
	dfs(x);
	int maks = x;
	for(int i = 1 ; i <= n ; i++)
		if(dst[i] >= dst[maks]) {
			maks = i;
		}
	return maks;	
}

void read() {
	cin >> n >> m;
	for(int i = 0 ; i < m ; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
}

int main() {
	read();
	int root = 1;
	root = getFarthest(root);
	cout << dst[getFarthest(root)] << endl;
	return 0;
}