#include <bits/stdc++.h>
using namespace std;

long long C[805][10];

long long comb(int x,int y) {
	if(x < y) return 0;
	if(y == 0) return 1;
	long long &ret = C[x][y];
	if(ret != -1) return ret;
	return ret = comb(x - 1,y) + comb(x - 1,y - 1);
}

int main() {
	memset(C,-1,sizeof C);
	int n; cin >> n;
	cout << comb(n + 4,5) * comb(n + 2,3) << endl;
	return 0;
}