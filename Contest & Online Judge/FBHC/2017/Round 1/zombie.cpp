#include <bits/stdc++.h>
using namespace std;

const int N = 55;

int x[N], y[N];
int n, r;

bool isInsideSquare(int xSquare, int ySquare, int xPoint, int yPoint) {
	return xSquare <= xPoint && xPoint <= xSquare+r && ySquare-r <= yPoint && yPoint <= ySquare;
}

void read() {
	scanf("%d %d",&n,&r);
	for(int i = 0 ; i < n ; i++)
		scanf("%d %d",x + i,y + i);
}

int solve() {
	int ret = 0;

	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++)
			for(int k = 0 ; k < n ; k++)
				for(int l = 0 ; l < n ; l++) {
					int tot = 0;
					int xSquareOne = min(x[i], x[j]);
					int ySquareOne = max(y[i], y[j]);
					int xSquareTwo = min(x[k], x[l]);
					int ySquareTwo = max(y[k], y[l]);

					for(int it = 0 ; it < n ; it++)
						tot += (isInsideSquare(xSquareOne, ySquareOne, x[it], y[it]) || 
							    isInsideSquare(xSquareTwo, ySquareTwo, x[it], y[it]));

					ret = max(ret, tot);
				}

	return ret;			
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		printf("Case #%d: %d\n", tc, solve());
		cerr << tc << "\n";
	}
	return 0;
}