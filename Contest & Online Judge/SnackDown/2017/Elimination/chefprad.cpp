#include <bits/stdc++.h>
using namespace std;

const int N = 255;

int a[N], b[N];
bool matched[N];
int n, m, e;

void read() {
	cin >> n >> m >> e;
	for(int i = 0 ; i < n ; i++)
		cin >> a[i];
	for(int i = 0 ; i < m ; i++)
		cin >> b[i];
}

int solve(int x) {
	for(int i = 0 ; i < m ; i++)
		matched[i] = 0;

	int ret = 0;
	int j = 0;
	for(int i = 0 ; i < n ; i++) {
		while(j < m && abs((long long)a[i] + x - b[j]) > e && (long long)b[j] - (a[i] + x) <= e) {
			j++;
		}
		if(j < m && abs((long long)a[i] + x - b[j]) <= e) {
			ret++;
			j++;
		}
	}

	return ret;
}

int work() {
	sort(a, a + n);
	sort(b, b + m);

	int ret = 0;
	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < m ; j++) {
			int x = b[j]-e-a[i];
			ret = max(ret, solve(x));

			x = e + b[j] - a[i];
			ret = max(ret, solve(x));
		}

	return ret;
}

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		int ret = work();
		cout << ret << endl;
	}
	return 0;
}