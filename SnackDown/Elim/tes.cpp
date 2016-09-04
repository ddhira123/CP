#include <bits/stdc++.h>
using namespace std;

int randomRange(int l,int r) {
	return l + rand() % (r - l + 1);
}

int main() {
	int t = 50;
	printf("%d\n",t);
	for(int tc = 1 ; tc <= t ; tc++) {
		int n = randomRange(480,500);
		for(int i = 0 ; i < n ; i++) {
			printf("%d %c ",randomRange(480,500), rand() & 1 ? 'R' : 'L');
		}
		printf("%d\n",randomRange(480,500));
	}
	return 0;
}