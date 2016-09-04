#include <bits/stdc++.h>
using namespace std;

int m[16];
int r[16];
int n;

int fpb(int a,int b) {
	return b == 0 ? a : fpb(b, a % b);
}

int main() {
	cin >> n;
	for(int i = 0 ; i < n ; i++) cin >> m[i];
	for(int i = 0 ; i < n ; i++) cin >> r[i];
	int lcm = 1;
	for(int i = 0 ; i < n ; i++) lcm = lcm / fpb(lcm,m[i]) * m[i];
	int tot = 0;
	for(int i = 0 ; i < lcm ; i++) {
		bool ok = 0;
		for(int j = 0 ; j < n ; j++)
			if(i % m[j] == r[j]) ok = 1;
		tot += ok;
	}
	printf("%.10lf\n",(double)tot / lcm);
	return 0;
}