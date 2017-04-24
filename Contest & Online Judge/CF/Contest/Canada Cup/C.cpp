#include <bits/stdc++.h>
using namespace std;

int ans[3][15];

int dr[] = {0,-1,0,1,1,-1,-1,1};
int dc[] = {-1,0,1,0,-1,-1,1,1};

int main() {
	string s;
	cin >> s;
	int a, b;
	for(int i = 0 ; i < 27 ; i++)
		for(int j = i+1 ; j < 27 ; j++)
			if(s[i] == s[j]) {
				a = i;
				b = j;
				if(a+1 == b) {
					cout << "Impossible\n";
					return 0;
				}
				goto asu;
			}
	asu:
	memset(ans,-1,sizeof ans);
	if((b-a-1) % 2 == 1) {
		int start = 12 - (b-a-1) / 2;
		ans[0][start] = s[a];
		int iter = a+1;
		for(int i = start+1 ; i < 13 ; i++)
			ans[0][i] = s[iter++];
		for(int i = 12 ; i >= start ; i--)
			ans[1][i] = s[iter++];
	}
	else {
		int start = 12 - (b-a-1) / 2;
		ans[0][start] = s[a];
		int iter = a+1;
		for(int i = start+1 ; i < 13 ; i++)
			ans[0][i] = s[iter++];
		for(int i = 12 ; i > start ; i--)
			ans[1][i] = s[iter++];
	}

	int r = 0, c = 12 - (b-a-1) / 2;
	for(int i = a-1 ; i >= 0 ; i--) {
		for(int j = 0 ; j < 8 ; j++) {
			int nr = r + dr[j];
			int nc = c + dc[j];
			if(nr >= 0 && nr < 2 && nc >= 0 && nc < 13 && ans[nr][nc] == -1) {
				ans[nr][nc] = s[i];
				r = nr;
				c = nc;
				break;
			}
		}
	}	

	r = 0, c = 12 - (b-a-1) / 2;
	for(int i = b+1 ; i < 27 ; i++) {
		for(int j = 0 ; j < 8 ; j++) {
			int nr = r + dr[j];
			int nc = c + dc[j];
			if(nr >= 0 && nr < 2 && nc >= 0 && nc < 13 && ans[nr][nc] == -1) {
				ans[nr][nc] = s[i];
				r = nr;
				c = nc;
				//printf("%d %d %c\n",nr,nc,s[i]);
				break;
			}
		}
	}
	for(int i = 0 ; i < 2 ; i++) {
		for(int j = 0 ; j < 13 ; j++)
			printf("%c",ans[i][j]);
		puts("");
	}
	return 0;
}