#include <bits/stdc++.h>
using namespace std;

long long mul(long long x,long long y) {
	return x * y;
}

int main() {
	int n; cin >> n;
	cout << mul(n + 1,n + 1) + mul(n,n + 1) + mul(n,n) << endl;
	return 0;
}