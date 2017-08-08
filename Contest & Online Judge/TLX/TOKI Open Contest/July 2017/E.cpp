#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

long long ujung[N][2];
long long path[N][2];
long long answer;
vector<pair<int,int>> adj[N];
int n;

void read() {
	scanf("%d", &n);
	for(int i = 1 ; i < n ; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);

		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}
}

void dfs(int now, int prv) {
	ujung[now][0]++;

	for(pair<int,int> nex : adj[now]) {
		if(nex.first == prv) continue;
		dfs(nex.first, now);

		// ganjil
		if(nex.second & 1) {
			answer += (path[nex.first][0] + ujung[nex.first][0] * nex.second) * ujung[now][0];
			answer += path[now][0] * ujung[nex.first][0];

			answer += (path[nex.first][1] + ujung[nex.first][1] * nex.second) * ujung[now][1];
			answer += path[now][1] * ujung[nex.first][1];

			path[now][1] += (path[nex.first][0] + ujung[nex.first][0] * nex.second);
			path[now][0] += (path[nex.first][1] + ujung[nex.first][1] * nex.second);

			ujung[now][1] += ujung[nex.first][0];
			ujung[now][0] += ujung[nex.first][1];
		} else {
			answer += (path[nex.first][1] + ujung[nex.first][1] * nex.second) * ujung[now][0];
			answer += path[now][0] * ujung[nex.first][1];

			answer += (path[nex.first][0] + ujung[nex.first][0] * nex.second) * ujung[now][1];
			answer += path[now][1] * ujung[nex.first][0];

			path[now][1] += (path[nex.first][1] + ujung[nex.first][1] * nex.second);
			path[now][0] += (path[nex.first][0] + ujung[nex.first][0] * nex.second);

			ujung[now][1] += ujung[nex.first][1];
			ujung[now][0] += ujung[nex.first][0];
		}
	}
}

int main() {
	read();
	dfs(1, -1);
	printf("%lld\n", answer * 2);
	return 0;
}