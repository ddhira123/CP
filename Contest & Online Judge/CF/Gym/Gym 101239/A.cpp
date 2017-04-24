#include <bits/stdc++.h>
using namespace std;

double p, a, b, c, d;
int n;

double get(double k) {
	return p * (sin(a * k + b) + cos(c * k + d) + 2);
}

int main() {
	cin >> p >> a >> b >> c >> d >> n;

	double maks = get(1);
	double ret = 0;
	for(int i = 2 ; i <= n ; i++) {
		double cur = get(i);

		// printf("%.9lf %.9lf\n", maks, cur);

		ret = max(ret ,maks - cur);
		maks = max(maks, cur);
	}

	printf("%.9lf\n", ret);
	return 0;
}