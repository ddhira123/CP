#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t;  tc++) {
		int n, a, b;
		cin >> n >> a >> b;
		printf("Kasus #%d:\n", tc);

		for(int i = 1 ; i <= n ; i++) {
			if(i % a == 0 && i % b == 0) {
				printf("FJ\n");
			} else
			if(i % a == 0) {
				printf("Fat\n");
			} else
			if(i % b == 0) {
				printf("Jelly\n");
			} else {
				printf("%d\n", i);
			}
		}
	}
	return 0;
}