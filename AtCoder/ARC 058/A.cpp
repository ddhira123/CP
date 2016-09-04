#include <bits/stdc++.h>
using namespace std;

bool flag[10];
int n, k;

bool can(int x) {
	while(x) {
		if(flag[x % 10]) return 0;
		x /= 10;
	}
	return 1;
}

int main() {
	cin >> n >> k;
	for(int i = 1 ; i <= k ; i++) {
		int x; cin >> x;
		flag[x] = 1;
	}
	while(!can(n)) n++;
	cout << n << endl;
	return 0;
}