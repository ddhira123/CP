#include <bits/stdc++.h>
using namespace std;

const int N = 100000;
const long long LMT = (long long)1e18;

vector<long long> v;

void generate() {
	v.push_back(0);
	v.push_back(1);
	for(int i = 2 ; v.back() < LMT ; i++) {
		long long mul = 1;
		if(i % 4 == 0) mul = 3;
		else if((i % 4) <= 2) mul = 2;

		long long add = (v[i-1] - v[i-2]) * mul;
		v.push_back(v.back() + add);
	}
}

int getNim(long long x) {
	int idx = upper_bound(v.begin(),v.end(),x - 1) - v.begin();
	return (idx % 4);
}

int main() {
	generate();
	int t; scanf("%d",&t);

	for(int tc = 1 ; tc <= t ; tc++) {
		int n; scanf("%d",&n);
		int nimber = 0;

		for(int i = 1 ; i <= n ; i++) {
			long long x; scanf("%lld",&x);
			nimber ^= getNim(x);
		}

		printf("%s\n",nimber ? "Henry" : "Derek");
	}
	return 0;
}