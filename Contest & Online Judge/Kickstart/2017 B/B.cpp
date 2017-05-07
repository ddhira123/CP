#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;
const int MAGIC = 200;
const double MX = 1e3 + 5;

double x[N], y[N], w[N];
int n;

void read() {
	cin >> n;
	for(int i = 0 ; i < n ; i++) {
		cin >> x[i] >> y[i] >> w[i];
	}
}

double coba(double tx, double ty) {
	double ret = 0;
	for(int i = 0 ; i < n ; i++)
		ret += w[i] * max(fabs(tx - x[i]), fabs(ty - y[i]));
	return ret;
}

double coba(double tx) {
	double lo = -MX, hi = MX;
	for(int i = 0 ; i < MAGIC ; i++) {
		double p1 = lo + (hi - lo) / 3;
		double p2 = lo + 2 * (hi - lo) / 3;

		if(coba(tx, p1) > coba(tx, p2)) {
			lo = p1;
		} else {
			hi = p2;
		}
	}
	return coba(tx, lo);
}

double solve() {
	double lo = -MX, hi = MX;
	for(int i = 0 ; i < MAGIC ; i++) {
		double p1 = lo + (hi - lo) / 3;
		double p2 = lo + 2 * (hi - lo) / 3;

		if(coba(p1) > coba(p2)) {
			lo = p1;
		} else {
			hi = p2;
		}
	}
	return coba(lo);
}

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		double ret = solve();
		printf("Case #%d: %.9lf\n", tc, ret);
	}
	return 0;
}