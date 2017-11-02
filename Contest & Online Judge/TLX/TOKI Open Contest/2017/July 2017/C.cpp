#include <bits/stdc++.h>
using namespace std;

const int MX = 1e7 + 5;

int prime[MX];
map<int,int> cnt;
map<int,int> punya;
int n;

void init() {
	int tot = 0;
	for(int i = 2 ; i < MX ; i++)
		if(prime[i] == 0) {
			tot++;
			for(int j = i ; j < MX ; j += i)
				prime[j] = i;
		}
	// cout << tot << endl;
}

void add(vector<int> x) {
	map<int,int> m;
	for(int it : x) {
		int temp = it;

		while(temp != 1) {
			int div = prime[temp];
			int cntr = 0;

			while(prime[temp] == div) {
				cntr++;
				temp /= div;
			}

			if(!m.count(div)) {
				m[div] = cntr;
			} else {
				m[div] = max(m[div], cntr);
			}
		}
	}

	for(auto it : m) {
		punya[it.first]++;

		if(cnt[it.first] == 0)
			cnt[it.first] = it.second;
		else
			cnt[it.first] = min(cnt[it.first], it.second);
	}
}

void solve() {
	vector<pair<int,int>> ans;

	for(auto it : punya)
		if(it.second == n) {
			ans.push_back({it.first, cnt[it.first]});
		}

	cout << ans.size() << endl;
	for(auto it : ans) {
		printf("%d %d\n", it.first, it.second);
	}
}

int main() {
	init();

	cin >> n;
	for(int i = 0 ; i < n ; i++) {
		int k; scanf("%d", &k);
		vector<int> v(k);

		for(int &x : v)
			scanf("%d", &x);

		add(v);
	}

	solve();
	return 0;
}