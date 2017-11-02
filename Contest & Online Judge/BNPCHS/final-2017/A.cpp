#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		int n; cin >> n;

		if(tc > 1) puts("");
		printf("Kasus #%d:\n", tc);
		for(int i = 0 ; i < n ; i++) {
			for(int j = 0 ; j < n ; j++) {
				int mins = j;
				mins = min(mins, n-j-1);
				mins = min(mins, i);
				mins = min(mins, n-i-1);

				if(mins % 2 == 0) {
					printf("#");
				} else {
					printf(".");
				}
			}
			puts("");
		}
	}
	return 0;
}