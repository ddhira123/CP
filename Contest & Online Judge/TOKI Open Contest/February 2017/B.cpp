#include <bits/stdc++.h>
using namespace std;

const int N = 155;
const int MX = 9e8;

int a[N], b[N], s[N];
vector<int> adj[N];
bool vis[N];
int match[N];
int n, m;

void buildGraph(int x) {
	for(int i = 1 ; i <= n ; i++) {
		adj[i].clear();
	}

	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n ; j++)
			if(abs(s[i] - s[j]) <= x && b[i] <= a[j])
				adj[i].push_back(j);
}

int augment(int x) {
	if(vis[x]) return 0;
	vis[x] = 1;

	for(int nex : adj[x])
		if(match[nex] == -1 || augment(match[nex])) {
			match[nex] = x;
			return 1;
		}

	return 0;
}

int MCBM(int x) {
	buildGraph(x);
	memset(match, -1, sizeof match);

	int ret = 0;
	for(int i = 1 ; i <= n ; i++) {
		memset(vis, 0, sizeof vis);
		ret += augment(i);
	}

	return ret;
}

void read() {
	cin >> n >> m;
	for(int i = 1 ; i <= n ; i++)
		cin >> s[i] >> a[i] >> b[i];
}

int work() {
	int lo = 0, hi = MX;

	while(lo < hi) {
		int mid = (lo + hi) / 2;

		if(n-MCBM(mid) <= m) {
			hi = mid;
		} else {
			lo = mid+1;
		}
	}

	if(n-MCBM(lo) > m)
		return -1;
	return lo;
}

int main() {
	read();
	cout << work() << "\n";
	return 0;
}