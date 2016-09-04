#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

double x[4], d[4];
double ans[4];
int n;
double g;
double PI = acos(-1);

int main() {
	cin >> n >> g;
	for(int i = 0 ; i < n ; i++)
		cin >> x[i] >> d[i];
	double tot = 0;
	for(int i = n - 1 ; i >= 0 ; i--) {
		tot += (cos(d[i] * PI / 180) * x[i]);
		ans[i] = sqrt(2 * g * tot);
	}
	for(int i = 0 ; i < n ; i++)
		printf("%.10lf\n",ans[i]);
	return 0;
}