#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct line {
	int y;
	int xa;
	int xb;

	int getWidth() {
		return xb - xa;
	}

	bool operator <(line other) const {
		return y < other.y;
	}

	void print() {
		printf("%d %d %d\n", y, xa, xb);
	}
};

struct event {
	double x;
	int val;

	bool operator <(event other) const {
		if(fabs(x-other.x) < EPS)
			return val > other.val;
		return x < other.x;
	}
};

vector<line> arr;
vector<event> v;
int n;

bool read() {
	if(scanf("%d", &n) != 1) return false;
	arr.clear();
	for(int i = 0 ; i < n ; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		// assert(a <= b);
		if(a > b) swap(a, b);

		arr.push_back((line){c, a, b});
	}

	return true;
}

double getX(double xa, int ya, double xb, int yb) {
	if(fabs(xa-xb) < EPS) return xa;

	ya = -ya;
	yb = -yb;
	double grad = (double)(yb-ya) / (xb-xa);

	return xa - ya / grad;
}

long long calc(line x, int flag) {
	v.clear();

	for(line y : arr) {
		if(y.y == x.y) continue;
		double xx1, xx2;
		// y.print();
		if(flag == 0) {
			xx1 = getX(x.xb, x.y, y.xa, y.y);
			xx2 = getX(x.xb, x.y, y.xb, y.y);
		} else  if(flag == 1){
			xx1 = getX(x.xa, x.y, y.xa, y.y);
			xx2 = getX(x.xa, x.y, y.xb, y.y);
		} 

		if(y.y > x.y) {
			swap(xx1, xx2);
		}
		v.push_back((event){xx1, y.getWidth()});
		v.push_back((event){xx2, -y.getWidth()});
	}

	sort(v.begin(), v.end());
	long long ret = 0;
	long long tot = 0;

	for(event ev : v) {
		tot += ev.val;
		ret = max(ret ,tot);
	}

	return ret;
}

long long solve() {
	long long ret = 0;
	for(line x : arr) {
		// x.print();
		for(int j = 0 ; j < 2 ; j++)
			ret = max(ret, x.getWidth() + calc(x, j));
	}
	return ret;
}

int main() {
	while(read()) {
		printf("%lld\n", solve());
	}
}