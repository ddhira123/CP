// WA
#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		int n, k; scanf("%d %d",&n,&k);
		int kiri = 3; 
		int kanan = 2001;
		int x = 1; 
		int y = 1500;
		if(k == 0) {
			x = 1;
			y = 2998;
		}
		printf("%d %d\n",x,y);
		for(int i = 0 ; k > 0 ; i++) {
			n -= 2;

			if(i >= k) {
				if(k % 2 == 1) {
					x = k+1;
					printf("%d %d\n",x,y);
				}
				else {
					x = 2001 - k + 1;
					printf("%d %d\n",x,y);
				}

				if(i % 2 == 1) {
					y = 2;
					printf("%d %d\n",x,y);
				}
				else {
					y = 2998;
					printf("%d %d\n",x,y);
				}
				k = 0;
				break;
			}
			if(i % 2 == 0) {
				x = kanan;
				kanan -= 2;
				printf("%d %d\n",x,y);
				y = 1500 + (i+2) / 2;
				printf("%d %d\n",x,y);
			}
			else {
				x = kiri;
				kiri += 2;
				printf("%d %d\n",x,y);
				y = 1500 - (i+2) / 2;
				printf("%d %d\n",x,y);
			}
			//assert(x >= 1 && x <= 3000 && y >= 1 && y <= 3000);
			k -= i;
		}
		assert(k == 0);
		assert(n >= 0);
		for(int i = 0 ; n > 1 ; i++) {
			n -= 2;
			printf("%d %d\n",++x,y);
			if(i % 2 == 0) {
				printf("%d %d\n",x,++y);
			}
			else {
				printf("%d %d\n",x,--y);
			}
		}
		if(n > 0)
			printf("%d %d\n",++x,y);
	}
	return 0;
}