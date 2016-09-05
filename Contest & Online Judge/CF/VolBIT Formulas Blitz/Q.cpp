#include <bits/stdc++.h>
using namespace std;

int main() {
	double l3,l4,l5;
	cin >> l3 >> l4 >> l5;
	double tri = sqrt(2) * l3 * l3 * l3 / 12;
	double sqr = sqrt(2) * l4 * l4 * l4 / 6;
	double pen = (5 + sqrt(5)) * l5 * l5 * l5 / 24;
	printf("%.10lf\n",tri + sqr + pen);
	return 0;
}