#include <bits/stdc++.h>
using namespace std;

int main() {
	int m; cin >> m;
	int arr[15];
	for(int i = 1 ; i <= 12 ; i++) cin >> arr[i];

	int a = -1, b = -1, profit = -1;
	for(int i = 1 ; i <= 12 ; i++)
		for(int j = i+1 ; j <= 12 ; j++) {
			int t = m / arr[i];
			int p = t * (arr[j] - arr[i]);
			if(p > profit) {
				a = i;
				b = j;
				profit = p;
			}
			else if(p == profit && arr[i] < arr[a]) {
				a = i;
				b = j;
			}
		}

	if(profit <= 0) printf("IMPOSSIBLE\n");
	else printf("%d %d %d\n",a,b,profit);	
	return 0;
}