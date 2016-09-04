#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a,long long b) {
	return b == 0 ? a : gcd(b,a % b);
}

long long x,y;

int main() {
	cin >> x >> y;
	x += y;
	cout << x % gcd(3701635544521223ll,700309427341853ll) << endl;
	return 0;
}