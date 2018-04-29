#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second

const int N = 1e5 + 5;

int y[N];
int n, a ,b;

long long cross(pii p, pii q, pii r) {
	long long dx1 = q.fi - p.fi;
	long long dy1 = q.se - p.se;
	long long dx2 = r.fi - p.fi;
	long long dy2 = r.se - p.se;

	return dx1 * dy2 - dy1 * dy2;
}

long long crossDriver(int p, int q, int r) {
	return cross({p, y[p]}, {q, y[q]}, {r, y[r]});
}

long long calc() {
	if(a > b) {
		reverse(y, y + n);
		a = n - a - 1;
		b = n - b - 1;
	}

	if(a+1 >= b) return 0;

	int piv = a+1;
	for(int i = a+2 ; i < b ; i++) {
		if(crossDriver(a, piv, i) >= 0)
			piv = i;
	}

	if(crossDriver(a, piv, b) > 0) {
		return 0;
	}

	long long dy = y[piv] - y[a];
	long long dx = piv - a;
	double ret = y[a] + (double)dy / dx * (b - a);
	ret = (long long)floor(ret) + 1;


	return ret - y[b];
}

int main() {
	int t; scanf("%d", &t);

	for(int tc = 1 ; tc <= t ; tc++) {
		scanf("%d %d %d", &n, &a, &b);
		a--; b--;
		swap(a, b);
		
		for(int i = 0 ; i < n ; i++) {
			scanf("%d", y + i);
		}

		long long ret = calc();

		printf("Case #%d: %lld\n", tc ,ret);
	}
	return 0;
}