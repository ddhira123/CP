#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

double PI = acos(-1);
double EPS = 1e-9;
int MAGIC = 1e8;

double toRad(double x) {
	return x / 180.0 * PI;
}

double get(double c,int part) {
	double deg = 360.0 / part;
	double sisa = (180 - deg) / 2;
	double x = 2*c * sin(toRad(sisa)) / sin(toRad(deg));
	x -= c;
	return x;
}

int getI(double c,double tgt,double buff) {
	int lo = 3, hi = MAGIC;
	while(lo < hi) {
		int mid = (lo + hi) / 2;
		if(get(c,mid) + buff > tgt + EPS)
			hi = mid;
		else
			lo = mid + 1;
		//cout << lo << " " << hi << endl;
	}
	//cout << lo <<  " " << get(c,lo) << endl;
	return lo;
}

int main() {
	double a,b,c;
	cin >> a >> b >> c;
	int ans = getI(c,b,0) - getI(c,a,2*EPS);
	cout << ans << endl;
	return 0;
}