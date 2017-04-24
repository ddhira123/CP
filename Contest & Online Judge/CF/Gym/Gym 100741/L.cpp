#include <bits/stdc++.h>
using namespace std;

map<long long, int> get(vector<int> v) {
	map<long long, int> m;

	for(int i = 0 ; i < (1<<v.size()) ; i++) {
		long long sum = 0;
		for(int j = 0 ; j < v.size() ; j++)
			if(i & (1<<j)) {
				sum += v[j];
			}
		m[sum]++;	
	}

	return m;
}

int sz[2];
vector<int> v[2];
map<long long, int> cnt[2];

int main() {
	cin >> sz[0] >> sz[1];
	for(int iter = 0 ; iter < 2 ; iter++) {
		for(int i = 0 ; i < sz[iter] ; i++) {
			int x; cin >> x;
			v[iter].push_back(x);
		}

		cnt[iter] = get(v[iter]);
	}

	long long ret = 0;
	for(pair<long long,int> x : cnt[0]) {
		ret += 1ll * x.second * cnt[1][x.first];
	}

	cout << ret-1 << "\n";
	return 0;
}