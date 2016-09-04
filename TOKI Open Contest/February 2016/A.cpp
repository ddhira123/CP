#include <bits/stdc++.h>
using namespace std;

int arr[1005];
int n,k;

int main() {
	cin >> n >> k;
	for(int i = 0 ; i < n ; i++) cin >> arr[i];
	sort(arr,arr + n);
	int ans = (int)2e9;
	for(int i = k - 1 ; i < n ; i++) ans = min(ans,arr[i] - arr[i - k + 1]);
	cout << ans << endl;
	return 0;
}