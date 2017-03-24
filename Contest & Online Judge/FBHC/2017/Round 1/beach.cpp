#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL MOD = 1e9 + 7;
const int N = 2e3 + 5;

LL inverse[N];

LL modPow(LL base,int po) {
	LL ret = 1;
	while(po) {
		if(po & 1) ret = ret * base % MOD;
		base = base * base % MOD;
		po >>= 1;
	}
	return ret;
}

LL getInverse(int x) {
	if(inverse[x])
		return inverse[x];
	return inverse[x] = modPow(x,MOD-2);
}

map<int, LL> mem;
int n, m;
int arr[N];

LL getFromCombination(int gap,int n2) {
	if(mem.count(gap))
		return mem[gap];
	LL ret = 1;
	for(int i = gap+n2 ; i > gap ; i--)
		ret = ret * i % MOD;
	return mem[gap] = ret;
}

LL getWays(int gap,int n2) {
	LL ret = 1ll * (gap+n2+1) * (gap+n2+2) % MOD;
	ret = ret * getFromCombination(gap,n2) % MOD;
	ret = ret * getInverse(n2+1) % MOD;
	ret = ret * getInverse(n2+2) % MOD;
	return ret;
}

LL solve() {
	if(n == 1)
		return m;

	mem.clear();
	LL ret = 0;
	int total = accumulate(arr,arr + n,0);

	for(int i = 0 ; i < n ; i++)
		for(int j = i+1 ; j < n ; j++) {
			int mSisa = m - arr[i] - arr[j] - 1;
			int totalSisa = total - arr[i] - arr[j];
			totalSisa *= 2;

			if(mSisa >= totalSisa) {
				LL ways = getWays(mSisa - totalSisa, n-2);
				ways = 2 * ways % MOD;
				ret = (ret + ways) % MOD;
			}
		}

	return ret;		
}

void read() {
	scanf("%d %d",&n,&m);
	for(int i = 0 ; i < n ; i++)
		scanf("%d",&arr[i]);
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		printf("Case #%d: %lld\n", tc, solve());
		cerr << tc << "\n";
	}
	return 0;
}