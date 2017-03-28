#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int x[N], y[N];
int n;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	cin >> n;
	for(int i = 0 ; i < n ; i++) {
		cin >> x[i] >> y[i];
	}

	sort(x, x + n);
	sort(y, y + n);

	cout << x[n/2] << " " << y[n/2] << "\n";
	return 0;
}