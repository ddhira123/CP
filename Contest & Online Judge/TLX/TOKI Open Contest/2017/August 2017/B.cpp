#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

char s[N][N];
int mx[4][N][N];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 0 ; i < n ; i++) {
		scanf("%s", s[i]);
	}

	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++)
			if(s[i][j] == '#') {
				mx[0][i][j] = 1 + (i > 0 && j > 0 ? mx[0][i-1][j-1] : 0);
			}
	for(int i = n-1 ; i >= 0 ; i--)
		for(int j = 0 ; j < n ; j++)
			if(s[i][j] == '#') {
				mx[1][i][j] = 1 + (i+1 < n && j > 0 ? mx[1][i+1][j-1] : 0);
			}
	for(int i = 0 ; i < n ; i++)
		for(int j = n-1 ; j >= 0 ; j--)
			if(s[i][j] == '#') {
				mx[2][i][j] = 1 + (i > 0 && j+1 < n ? mx[2][i-1][j+1] : 0);
			}
	for(int i = n-1 ; i >= 0 ; i--)
		for(int j = n-1 ; j >= 0 ; j--)
			if(s[i][j] == '#') {
				mx[3][i][j] = 1 + (i+1 < n && j+1 < n ? mx[3][i+1][j+1] : 0);
			}

	int ret = 0;
	for(int i = 1 ; i < n ; i++)
		for(int j = 1 ; j < n ; j++)
			if(s[i][j] == '#') {
				int mins = min(mx[1][i][j], mx[2][i][j]);
				mins = min(mins, mx[0][i][j]);
				mins = min(mins, mx[3][i][j]);
				ret += mins-1;
			}

	printf("%d\n", ret);
	return 0;
}