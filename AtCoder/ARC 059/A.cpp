#include <bits/stdc++.h>
using namespace std;

const int LMT = 100;
const int N = 105;

int arr[N];
int n;

int sqr(int x) {
	return x * x;
}

int main() {
	cin >> n;
	for(int i = 0 ; i < n ; i++) cin >> arr[i];

	int ans = 1e9;
	
	for(int i = -LMT ; i <= LMT ; i++) {
		int tot = 0;
		for(int j = 0 ; j < n ; j++)
			tot += sqr(arr[j] - i);
		ans = min(ans,tot);
	}

	cout << ans << endl;
	return 0;
}