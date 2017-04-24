#include <bits/stdc++.h>
using namespace std;

vector<int> v[505];
int ans[505];
int e, n, t;

int main() {
	cin >> n >> t;
	cin >> e;
	for(int i = 0 ; i < e ; i++) {
		int a, b;
		cin >> a >> b;
		v[a].push_back(b);
	}

	bool ok = 1;
	for(int i = 1 ; i <= n ; i++) {
		if(i == t) continue;
		sort(v[i].begin(),v[i].end());
		int l = 0, r = (int)(v[i].size()) - 1;
		while(l <= r) {
			if(v[i][r] == 0) {
				puts("IMPOSSIBLE");
				return 0;
			}
			ans[i]++;
			l += (v[i][r]-1);
			r--;
		}
	}
	for(int i = 1 ; i <= n ; i++) cout << ans[i] << " ";
	return 0;
}