#include <bits/stdc++.h>
using namespace std;

int dr[4] = {-1,0,1,0};
int dc[4] = {0,-1,0,1};

int r, c;
char arr[20][20];
char ori[20][20];

void convert(char &x) {
	x = (x == '.') ? 'X' : '.';
}

void toggle(int rr,int cc) {
	convert(arr[rr][cc]);
	for(int i = 0 ; i < 4 ; i++) {
		int nr = rr + dr[i];
		int nc = cc + dc[i];
		if(nr >= 0 && nr < r && nc >= 0 && nc < c)
			convert(arr[nr][nc]);
	}
}

int solve() {
	int ret = 1e9;
	if(r < c) {
		for(int i = 0 ; i < r ; i++)
			for(int j = i+1 ; j < c ; j++)
				swap(ori[i][j],ori[j][i]);
		swap(r,c);	
	}
	for(int bm = 0 ; bm < (1<<c) ; bm++) {
		int tot = 0;

		for(int iter = 0 ; iter < r ; iter++)
			for(int i = 0 ; i < c ; i++)
				arr[iter][i] = ori[iter][i];

		for(int j = 0 ; j < c ; j++)
			if(bm & (1<<j)) {
				tot++;
				toggle(0,j);
			}

		for(int i = 1 ; i < r && tot < ret ; i++)
			for(int j = 0 ; j < c && tot < ret ; j++)
				if(arr[i-1][j] == 'X') {
					toggle(i,j);
					tot++;
				}	

		for(int i = 0 ; i < c && tot < ret; i++)
			if(arr[r-1][i] == 'X')
				tot = 1e9;

		ret = min(ret,tot);				
	}

	return ret > r*c ? -1 : ret;
}

char dummy[30];

int main() {
	while(scanf("%d %d",&r,&c) == 2 && r > 0 && c > 0) {
		for(int i = 0 ; i < r ; i++) {
			scanf("%s",ori[i]);
		}
		int ret = solve();
		if(ret == -1)
			printf("Damaged billboard.\n");
		else
			printf("You have to tap %d tiles.\n",ret);
	}
	return 0;
}