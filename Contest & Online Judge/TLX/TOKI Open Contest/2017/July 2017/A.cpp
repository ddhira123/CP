#include <bits/stdc++.h>
using namespace std;

int n;

int rec(int a, int b, int c) {
	if(a + b + c == n) {
		return b == c;
	}

	int ret = 0;
	ret += rec(a+1, b, c);
	ret += rec(a, b+1, c);
	ret += rec(a, b, c+1);

	return ret;
}

int main() {
	cin >> n;
	cout << rec(0, 0, 0) << endl;
	return 0;
}