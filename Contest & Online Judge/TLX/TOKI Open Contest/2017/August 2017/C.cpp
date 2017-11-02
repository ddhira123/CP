#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int mx[N];
int arr[N];
int n, q;
vector<pair<int,int>> queries[N];
int ans[N];

void read() {
	scanf("%d %d", &n, &q);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d", arr + i);
	}
	for(int i = 1 ; i <= q ; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		queries[r].push_back({l, i});
	}
}

void solve() {
	for(int r = 1 ; r <= n ; r++) {
		mx[arr[r]] = (arr[r] == 1 ? r : mx[arr[r]-1]);

		for(pair<int,int> query : queries[r]) {
			int l = query.first;
			int idx = query.second;
			// printf("idx %d l %d\n", idx, l);

			int lo = 0, hi = n;
			while(lo < hi) {
				int mid = (lo + hi + 1) / 2;
				if(mx[mid] >= l) {
					lo = mid;
				} else {
					hi = mid-1;
				}
			}

			ans[idx] = lo;
		}
	}
	for(int i =1 ; i <= q ; i++)
		printf("%d\n", ans[i]);
}

int main() {
	read();
	solve();
	return 0;
}