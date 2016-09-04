#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

const LL MOD = 1e9 + 7;
LL a;

LL modPow(LL base,LL po) {
	LL ret = 1;
	while(po) {
		if(po & 1) ret = (ret * base) % MOD;
		base = (base * base) % MOD;
		po >>= 1;
	}
	return ret;
}

int main() {
	cin >> a;
	cout << modPow(2,a) << endl;
	return 0;
}