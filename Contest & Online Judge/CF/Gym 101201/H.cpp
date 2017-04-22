#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 2e5 + 5;

vector<LL> v;
LL l[N], r[N];
vector<int> adj[2*N];
long long dp[2*N];
LL n;
int k;

int getId(LL x) {
	return lower_bound(v.begin(), v.end(), x) - v.begin();
}

void read() {
	cin >> n >> k;
	for(int i = 0 ; i < k ; i++) {
		cin >> l[i] >> r[i];
	}
}

void prepare() {
	for(int i = 0 ; i < k ; i++) {
		v.push_back(l[i]);
		v.push_back(r[i]);
	}

	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());

	for(int i = 0 ; i < k ; i++) {
		l[i] = getId(l[i]);
		r[i] = getId(r[i]);

		adj[l[i]].push_back(r[i]);
	}

	memset(dp, -1, sizeof dp);
}

LL solve(int now) {
	if(now == v.size()) return 0;
	LL &ret = dp[now];

	if(ret != -1) return ret;
	ret = solve(now+1);

	for(int nex : adj[now]) {
		LL len = v[nex] - v[now] + 1;
		ret = max(ret, len + solve(nex+1));
	}

	return ret;
}

int main() {
	read();
	prepare();
	cout << n-solve(0) << endl;
	return 0;
}