#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		int n; cin >> n;
		vector<int> w(n), h(n);
		for(int i = 0 ; i < n ; i++) cin >> w[i];
		for(int i = 0 ; i < n ; i++) cin >> h[i];
		sort(w.begin()+1,w.end());
		sort(h.begin(),h.end());

		int brave = w[0] * h.back();
		bool ok = 1;
		for(int i = 1 ; i < w.size() ; i++)
			if(w[i] * h[n-i-1] >= brave)
				ok = 0;

		if(ok) cout << "YES\n";
		else cout << "NO\n";	
	}
	return 0;
}