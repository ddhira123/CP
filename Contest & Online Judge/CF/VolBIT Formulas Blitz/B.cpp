#include <bits/stdc++.h>
using namespace std;

const double DIFF = 1.000000011;

int main() {
	double n,t;
	scanf("%lf %lf",&n,&t);
	printf("%.10lf\n",n*pow(DIFF,t));
	return 0;
}