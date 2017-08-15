#include <bits/stdc++.h>
using namespace std;

const int N = 50005;
const int MX = 2001;

int x[N], y[N];
int cnt_x[MX], cnt_y[MX];
int n;
long long k;
long long sum_dist_x[MX], sum_dist_y[MX];

void read() {
	scanf("%d %lld", &n, &k);
	for(int i = 0 ; i < n ; i++) {
		scanf("%d %d", x + i, y + i);
	}
}

void init() {
	memset(cnt_x, 0, sizeof cnt_x);
	memset(cnt_y, 0, sizeof cnt_y);

	for(int i = 0 ; i < n ; i++) {
		cnt_x[x[i]]++;
		cnt_y[y[i]]++;
	}

	// sum_dist stuff
	for(int i = 0 ; i < MX ; i++) {
		sum_dist_x[i] = sum_dist_y[i] = 0;
		
		for(int j = 0 ; j < MX ; j++) {
			sum_dist_x[i] += 1ll * abs(j - i) * cnt_x[j];
			sum_dist_y[i] += 1ll * abs(j - i) * cnt_y[j]; 
		}
	}

	// reduce k
	for(int i = 0 ; i < MX ; i++)
		for(int j = i ; j < MX ; j++) {
			k -= 1ll * cnt_x[i] * cnt_x[j] * (j - i);
			k -= 1ll * cnt_y[i] * cnt_y[j] * (j - i);
		}
}

void solve() {
	bool found = 0;
	for(int i = 0 ; i < MX && !found ; i++)
		for(int j = 0 ; j < MX && !found ; j++)
			if(sum_dist_x[i] + sum_dist_y[j] == k) {
				printf("%d %d\n", i, j);
				found = true;
			}
	if(!found) {
		puts("-1 -1");
	}
}

int main() {
	int t; scanf("%d", &t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		init();
		solve();
	}
	return 0;
}
