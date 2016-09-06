#include <bits/stdc++.h>
using namespace std;

const int N = 1030;

int arr[N][N];
int BIT[N][N];
int r,c;

void update(int x,int y,int val) {
	for(int i = x ; i <= r ; i += i & -i)
		for(int j = y ; j <= c ; j += j & -j) 
			BIT[i][j] += val;
}

int query(int x,int y) {
	int ret = 0;

	for(int i = x ; i > 0 ; i -= i & -i)
		for(int j = y ; j > 0 ; j -= j & -j)
			ret += BIT[i][j];

	return ret;	
}

void updateWorker(int x,int y,int val) {
	update(x,y,val - arr[x][y]);
	arr[x][y] = val;
}

int queryWorker(int r1,int c1,int r2,int c2) {
	int ret = query(r2,c2);
	ret -= query(r1 - 1,c2);
	ret -= query(r2,c1 - 1);
	ret += query(r1 - 1,c1 - 1);

	return ret;
}

int main() {
	int t; scanf("%d",&t);

	for(int tc = 1 ; tc <= t ; tc++) {
		scanf("%d",&r); c = r;

		char opt[5];
		scanf("%s",opt);

		while(opt[0] != 'E') {

			if(opt[1] == 'E') {
				int x,y,val;
				scanf("%d %d %d",&x,&y,&val);
				x++; y++;
				updateWorker(x,y,val);
			}
			else {
				int r1,c1,r2,c2;
				scanf("%d %d %d %d",&r1,&c1,&r2,&c2);
				r1++; c1++; r2++; c2++;
				printf("%d\n",queryWorker(r1,c1,r2,c2));
			}
			scanf("%s",opt);
		}

		puts("");

		for(int i = 1 ; i <= r ; i++)
			for(int j = 1 ; j <= c ; j++)
				arr[i][j] = BIT[i][j] = 0;
	}
	return 0;
}