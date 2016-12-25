#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	k--;
	int col = k / (2*m);
	int row = (k % (2*m)) / 2;
	char pos = k & 1 ? 'R' : 'L';

	cout << col+1 << " " << row+1 << " " << pos << "\n";
	return 0;
}