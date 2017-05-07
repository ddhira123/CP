#include <bits/stdc++.h>
using namespace std;

int main() {
	long long a, b, c;
	long long n, m;
	cin >> a >> b >> c >> n >> m;

	long long ret = min(min(n, c+a), min(m, c+b));
	if(c + a <= n) {
		ret = max(ret, min(m, c+b));
	}
	if(c + b <= m) {
		ret = max(ret, min(n, c+a));
	}
	if(c+a <= n && c+b <= m) {
		ret = a + b + c;
	}

	cout << ret << endl;
	return 0;
}