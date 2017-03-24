#include <bits/stdc++.h>
using namespace std;

const int MX = 1e7 + 5;

int divisor[MX];

void precompute() {
	for(int i = 1 ; i < MX ; i++)
		for(int j = i+i ; j < MX ; j += i)
			divisor[j] += i;
}

long long solve(int a, int b) {
	long long ret = 0;
	for(int i = a ; i <= b ; i++)
		ret += (i >= divisor[i] ? i-divisor[i] : divisor[i]-i);
	return ret;
}

int main() {
	precompute();
	int a, b; cin >> a >> b;
	printf("%lld\n", solve(a, b));
	return 0;
}