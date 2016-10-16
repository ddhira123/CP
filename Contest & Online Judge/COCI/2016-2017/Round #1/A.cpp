#include <bits/stdc++.h>
using namespace std;

int main() {
	int x, n, ret, temp;
	cin >> x;
	ret = x;
	cin >> n;
	for(int i = 1 ; i <= n ; i++) {
		cin >> temp;
		ret += x - temp;
	}
	cout << ret << "\n";
	return 0;
}