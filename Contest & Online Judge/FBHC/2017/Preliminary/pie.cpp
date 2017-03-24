#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second

const pii P1 = {50,50};
const pii P2 = {50,100};

double PI = acos(-1);

double degreeToRadian(double x) {
	return x / 360 * 2 * PI;
}

int sqr(int x) {
	return x*x;
}

int squaredDistance(pii a,pii b) {
	return sqr(a.fi - b.fi) + sqr(a.se - b.se);
}

double euclidDistance(pii a,pii b) {
	return hypot(a.fi - b.fi, a.se - b.se);
}

double getAngle(pii center,pii a,pii b) {
	int c2 = squaredDistance(a,b);
	int a2 = squaredDistance(a,center);
	int b2 = squaredDistance(b,center);
	//printf("%d %d %d\n",a2, b2, c2);
	double divisor = -2 * euclidDistance(a, center) * euclidDistance(b, center);
	double coss = (c2 - a2 - b2) / divisor;
	//printf("cos -> %.6lf degree -> %.6lf\n",coss,acos(coss));
	return acos(coss);
}

bool isBlack(int p,int x,int y) {
	if(p == 0) return 0;
	pii pnt = {x,y};
	if(squaredDistance(pnt, P1) > 2500) return 0;

	double angle;
	if(x >= 50)
		angle = getAngle(P1,P2,pnt);
	else
		angle = 2*PI - getAngle(P1,P2,pnt);

	double barAngle = degreeToRadian(1.0 * p * 360 / 100);

	//printf("%.10lf %.10lf\n",angle, barAngle);

	if(barAngle + 1e-7 > angle)
		return 1;

	return 0;
}

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		int p, x, y;
		cin >> p >> x >> y;

		if(isBlack(p,x,y))
			cout << "Case #" << tc << ": black\n";
		else
			cout << "Case #" << tc << ": white\n";
	}
	return 0;
}