#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int MAX = 205;
const int MOD = 1e9 + 7;

struct Path {
	vector<int> v;

	void clear() {
		v.clear();
	}

	void add(int x) {
		v.push_back(x);
	}

	void pop() {
		v.pop_back();
	}

	bool operator <(const Path &other) const {
		int i = v.size()-1;
		while(i >= 0 && v[i] == 0) i--;
		int j = other.v.size()-1;
		while(j >= 0 && other.v[j] == 0) j--;

		if(i < j) return true;
		if(i > j) return false;
		for(int k = i ; k >= 0 ; k--) {
			if(v[k] < other.v[k]) return true;
			if(v[k] > other.v[k]) return false;
		}

		return false;
	}

	int getVal() {
		int ret = 0;
		int mul = 1;
		for(int i = 1 ; i < v.size() ; i++) {
			mul = 1ll * mul * i % MOD;
			ret = (ret + 1ll * mul * v[i]) % MOD;
		}
		return ret;
	}
};

int n, m;
vector<pair<int,int>> adj[N];
Path dp[2][N];

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0 ; i < m ; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
}

int solve() {
	dp[0][1].add(0);
	Path ans;

	for(int iter = 0 ; iter < MAX; iter++) {
		int bit = iter & 1;
		int nbit = bit ^ 1;

		for(int i = 1 ; i <= n ; i++) {
			dp[nbit][i].clear();
		}
		for(int i = 1 ; i <= n ; i++) {
			if(!dp[bit][i].v.empty()) {
				// printf("reach %d %d\n", iter, i);
				for(pair<int,int> edge : adj[i]) {
					int nxt = edge.first;
					int cost = edge.second;

					if(cost <= iter) {
						dp[bit][i].add(cost);

						if(dp[nbit][nxt].v.empty() || dp[bit][i] < dp[nbit][nxt]) {
							dp[nbit][nxt] = dp[bit][i];
						}

						dp[bit][i].pop();
					}
				}
			}
		}

		if(!dp[bit][n].v.empty() && (ans.v.empty() || dp[bit][n] < ans)) {
			ans = dp[bit][n];
		}
	}

	if(ans.v.empty()) {
		return -1;
	} else {
		return ans.getVal();
	}
}

int main() {
	read();
	printf("%d\n", solve());
	return 0;
}