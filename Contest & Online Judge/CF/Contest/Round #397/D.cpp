#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> v[N];

int f[N];
int g[N];
int n;

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d", f + i);
	}
}

void solve() {
	for(int i = 1 ; i <= n ; i++)
		v[f[i]].push_back(i);

	vector<int> h;
	for(int i = 1 ; i <= n ; i++) {
		if(v[i].empty()) continue;

		bool ada = 0;
		for(int x : v[i])
			if(x == i)
				ada = 1;

		if(ada) {
			h.push_back(i);
			for(int x : v[i])
				g[x] = h.size();
		} else {
			puts("-1");
			return;
		}
	}

	printf("%d\n",(int)h.size());
	for(int i = 1 ; i <= n ; i++)
		printf("%d ",g[i]);
	puts("");
	for(int x : h)
		printf("%d ", x);
}

int main() {
	read();
	solve();
	return 0;
}