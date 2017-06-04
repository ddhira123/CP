#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		int x; scanf("%d",&x);
		if(x == 1) {
			printf("1\n1\n");
		}
		else {
			int n = 1;
			int msb = 0;
			int bit = 0;
			int lsb = 100;
			for(int i = 0 ; i < 17 ; i++)
				if(x & (1<<i)) {
					msb = i;
					lsb = lsb == 100 ? i : lsb;
					bit++;
				}

			n += 2*msb;
			n += (msb - lsb);

			int atas = n - msb + lsb + 1;
			int bawah = 2;
			
			printf("%d\n",n);
			printf("1"); 
			for(int i = 0 ; i < msb ; i++) {
				if(x & (1<<i)) {
					int nb = i+1;
					while((x & (1<<nb)) == 0) nb++;
					for(int j = i ; j < nb ; j++)
						printf(" %d",atas++);
				}
				printf(" %d %d",bawah+1,bawah);
				bawah += 2;
			}	
			puts("");
		}
	}
	return 0;
}