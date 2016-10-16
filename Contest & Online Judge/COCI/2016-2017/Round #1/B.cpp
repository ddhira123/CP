// TLE
#include <bits/stdc++.h>
using namespace std;

const int ROW = 10;
const int N = 1e5;

char s[ROW+5][N+5];
int n;
bool can[ROW+5][N+5];

void read() {
	scanf("%d",&n);
	for(int i = 0 ; i < ROW ; i++)
		scanf("%s",s[i]);
}

void DP() {
	for(int i = 0 ; i < 10 ; i++)
		if(s[i][n-1] == '.')
			can[i][n-1] = 1;
	for(int j = n-2 ; j >= 0 ; j--)
		for(int i = 0 ; i < 10 ; i++)
			if(s[i][j] == '.')
				for(int k = max(0,i-1) ; k <= min(9,i+1) ; k++)
					can[i][j] |= can[k][j+1];			
}

void solve() {
	int nr = 9;
	int nc = 0;
	vector<pair<int,int>> ans;
	while(nc < n-1) {
		while(nc < n-1 && can[min(9,nr+1)][nc+1]) {
			nr = min(9,nr+1);
			nc++;
		}
		int lst = nc;
		while(nc < n-1 && can[max(0,nr-1)][nc+1]) {
			nr = max(0,nr-1);
			nc++;
		}
		if(nc != lst) {
			ans.push_back({lst,nc-lst});
		}
	}
	printf("%d\n",(int)ans.size());
	for(pair<int,int> x : ans)
		printf("%d %d\n",x.first,x.second);
}

int main() {
	read();
	DP();
	solve();
	return 0;
}