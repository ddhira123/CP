#include <bits/stdc++.h>
using namespace std;

const int N = (int)1e7 + 5;

int fak[N];

void pre() {
	for(int i = 2 ; i <= N ; i++)
		if(fak[i] == 0)
			for(int j = i ; j <= N ; j += i)
				fak[j] = i;
}

int getPrimeFactor(int x) {
	int ret = 0;
	while(x > 1) {
		ret++;
		x /= fak[x];
		//printf("%d\n",x);
	}
	//puts("");
	return ret;
}

int main() {
	pre();
	int t; scanf("%d",&t);
	for(int tc = 1; tc <= t ; tc++) {
		int n,k;
		scanf("%d %d",&n,&k);
		if(getPrimeFactor(n) == k)
			puts("Ya");
		else
			puts("Tidak");
	}
	return 0;
}