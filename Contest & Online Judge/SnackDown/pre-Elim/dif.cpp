#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		int n; scanf("%d",&n);
		for(int i = 0 ; i < n ; i++)
			printf("%c",(i % 26) + 'a');
		puts("");
	}
	return 0;
}