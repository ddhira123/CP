#include <bits/stdc++.h>
using namespace std;

vector<long long> t;
vector<long long> b;
int n, m;

int main() {
	scanf("%d %d", &n, &m);

	for(int i = 0 ; i < n ; i++) {
		int x; scanf("%d", &x);
		if(t.empty() || t.back() != x) {
			t.push_back(x);
		}
	}
	n = t.size();

	for(int i = 0 ; i < m ; i++) {
		int x; scanf("%d", &x);
		if(b.empty() || b.back() != x) {
			b.push_back(x);
		}
	}
	m = b.size();

	// printf("%d %d\n", n, m);
	long long ret = 0;
	for(int i = 0 ; i < m ;) {
		int up = lower_bound(t.begin(), t.end(), b[i]) - t.begin();
		int bawah = up-1;
		int j = i;

		if(up != n) {
			while(j < m && b[j] <= t[up]) j++;
		} else {
			j = m;
		}

		if(up == n) {
			ret += 2ll * (b[m-1] - t[bawah]);
			i = j;
		} else if(bawah == -1) {
			ret += 2ll * (t[up] - b[0]);
			i = j;
		} else {
			j--;
			long long mins = 2e9 + 1e8;
			// printf("%d\n", mins);
			mins = min(mins, b[j] - t[bawah] + min(b[j] - t[bawah], t[up] - b[j]));
			// printf("%d\n", mins);
			mins = min(mins, t[up] - b[i] + min(b[i] - t[bawah], t[up] - b[i]));

			// printf("%d\n", mins);
			for(int k = i ; k+1 <= j ; k++) {
				long long add = 2 * (b[k] - t[bawah]);
				add += 2 * (t[up] - b[k+1]);
				mins = min(mins, add);
			}

			// printf("%d %d %d\n", i, j, mins);
			ret += mins;
			i = j+1;
		}
	}

	printf("%lld\n", ret);
	return 0;
}