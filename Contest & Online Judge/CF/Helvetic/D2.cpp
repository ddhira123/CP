// C(n+1+c,c)
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e6 + 3;

long long modPow(long long base,int po) {
	long long ret = 1;
	while(po) {
		if(po & 1) ret = (ret * base) % MOD;
		base = (base * base) % MOD;
		po >>= 1;
	}
	return ret;
}

int getInverse(int x) {
	return modPow(x,MOD-2);
}

int getFactorial(int x) {
	long long ret = 1;
	for(int i = 1 ; i <= x ; i++)
		ret = (ret * i) % MOD;
	return ret;
}

int C(int a,int b) {
	long long ret = getFactorial(a);
	ret = (ret * getInverse(getFactorial(b))) % MOD;
	ret = (ret * getInverse(getFactorial(a-b))) % MOD;
	return ret;
}

int main() {
	int n, c;
	cin >> n >> c;
	cout << (C(n+c,c) + MOD - 1) % MOD << endl;
	return 0;
}