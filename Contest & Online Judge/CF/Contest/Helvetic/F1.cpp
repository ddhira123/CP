#include <bits/stdc++.h>
using namespace std;

int cnt[10005];

int main() {
	int n; cin >> n;
	long long ans = 0;
	for(int i = 1 ; i < n ; i++) {
		int a, b;
		cin >> a >> b;
		ans += (cnt[a] + cnt[b]);
		cnt[a]++; cnt[b]++;
	}
	cout << ans << endl;
	return 0;
}