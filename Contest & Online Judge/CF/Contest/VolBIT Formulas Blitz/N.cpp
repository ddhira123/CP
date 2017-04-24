#include <bits/stdc++.h>
using namespace std;

int main() {
	double a,b,c;
	cin >> a >> b >> c;
	double det = b * b - 4.0 * a * c;
	det = sqrt(det);
	double ans1 = (-b + det) / (2 * a);
	double ans2 = (-b - det) / (2 * a);
	printf("%.10lf\n%.10lf\n",max(ans1,ans2),min(ans1,ans2));
	return 0;
}