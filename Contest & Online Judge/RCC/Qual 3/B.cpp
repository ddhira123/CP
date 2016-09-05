#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		int len; cin >> len;
		string a,b; cin >> a >> b;

		int ans = 0;
		bool inve = 0;
		for(int i = 0 ; i +1 < len ; i++) {
			if((inve && a[i] == b[i]) || (!inve && a[i] != b[i])) {
				ans++;
				inve = 1;
			}
			else {
				inve = 0;
			}
		}

		// /cout << ans << " " << inve << endl;

		if((inve && a[len-1] == b[len-1]) || (!inve && a[len-1] != b[len-1]))
			ans = -1;

		cout << ans << "\n";
	}
	return 0;
}