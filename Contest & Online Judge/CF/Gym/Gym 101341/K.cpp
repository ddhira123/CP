#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

pair<long long, int> dp[2*N];
vector<pair<pair<int ,int>, int>> v[2*N];
pair<int, int> track[2*N];
int a[N], b[N], c[N];
vector<int> uniq;
int n;

void read() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d %d %d", a + i, b + i, c + i);
}

void prepare() {
	for(int i = 1 ; i <= n ; i++) {
		uniq.push_back(a[i]);
		uniq.push_back(b[i]);
	}

	sort(uniq.begin(), uniq.end());
	uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());
	for(int i = 1 ; i <= n ; i++) {
		a[i] = lower_bound(uniq.begin(), uniq.end(), a[i]) - uniq.begin();
		b[i] = lower_bound(uniq.begin(), uniq.end(), b[i]) - uniq.begin();

		v[a[i]].push_back({{b[i], i}, c[i]});
	}
}

void work() {
	for(int i = uniq.size()-1 ; i >= 0 ; i--) {
		dp[i] = dp[i+1];

		for(pair<pair<int ,int>, int> x : v[i]) {
			int nex = x.first.first;
			int idx = x.first.second;
			int len = uniq[nex] - uniq[i];
			int add = x.second;

			long long totC = add + dp[nex].first;
			int totLen = len + dp[nex].second;

			if(totC > dp[i].first) {
				dp[i] = {totC, totLen};
			}
			if(totC == dp[i].first) {
				dp[i].second = min(dp[i].second, totLen);
			}
		}
	}

	vector<int> use;
	for(int i = 0 ; i < uniq.size() ; ) {
		if(dp[i] == dp[i+1]) {
			i++;
		} else {
			for(pair<pair<int ,int>, int> x : v[i]) {
				int nex = x.first.first;
				int idx = x.first.second;
				int len = uniq[nex] - uniq[i];
				int add = x.second;

				long long totC = add + dp[nex].first;
				int totLen = len + dp[nex].second;

				if(totC == dp[i].first && totLen == dp[i].second) {
					use.push_back(idx);
					i = nex;
					break;
				}
			}
		}
	}

	printf("%d %lld %d\n", (int)use.size(), dp[0].first, dp[0].second);
	// sort(use.begin(), use.end());
	for(int x : use) printf("%d ", x);
	puts("");
}

int main() {
	read();
	prepare();
	work();
	return 0;
}