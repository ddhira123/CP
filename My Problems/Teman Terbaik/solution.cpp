#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);

	double probs = 0.5;
	double ret = 0;

	for(int i = 0 ; i < n ; i++) {
		int t, type;
		scanf("%d %d", &t, &type);

		ret += probs * t;

		if(type == 1) {
			probs /= 2;
		}
	}

	printf("%.5lf\n", ret);
	return 0;
}