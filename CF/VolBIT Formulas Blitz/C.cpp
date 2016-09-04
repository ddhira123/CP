#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	printf("%lld\n",(1ll << (n + 1)) - 2);
	return 0;
}