#include <bits/stdc++.h>
using namespace std;

bool match[1005][1005];

int main() {
	int n; scanf("%d",&n);
	int comb = n * (n-1) / 2;
	if(comb % n == 0) {
		int win = comb / n;
		for(int i = 0 ; i < n ; i++)
			for(int j = 0 ; j < win ; j++)
				match[i][(i + 1 + j) % n] = 1;
		for(int i = 0 ; i < n ; i++)
			for(int j = 0 ; j < n ; j++)
				assert(i == j || match[i][j] != match[j][i]);
		puts("Yes");
		for(int i = 0 ; i < n ; i++)
			for(int j = i+1 ; j < n ; j++)
				printf("%d%c",match[i][j], j+1 == n ? '\n' : ' ');	
	} else {
		puts("No");
	}
	return 0;
}