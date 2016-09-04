#include <bits/stdc++.h>
using namespace std;

const int N = 100000;

int grundy[N + 5];
int cnt[N + 5];
bool flag[N + 5];

void init() {
	for(int i = 2 ; i <= N ; i++)
		if(!flag[i]) {
			for(int j = i ; j <= N ; j += i) {
				flag[j] = 1;
				int temp = j;
				while(temp % i == 0) {
					temp /= i;
					cnt[j]++;
				}
			}
		}
		
	for(int i = 1 ; (1 << i) <= N ; i++) {
		set<int> seen;
		for(int j = 1 ; j < i ; j++)
			for(int k = 1 ; k < i ; k++)
				seen.insert(grundy[j] ^ grundy[k]);
		
		for(int j = 0 ; ; j++)
			if(!seen.count(j)) {
				grundy[i] = j;
				break;
			}		
		//printf("%d -> %d\n",i,grundy[i]);	
	}	
}

int main() {
	init();
	int t;
	scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		int n;
		scanf("%d",&n);
		
		int nimSum = 0;
		for(int i = 0 ; i < n ; i++) {
			int x;
			scanf("%d",&x);
			//printf("%d -> %d\n",x,grundy[x]);
			nimSum ^= grundy[cnt[x]];
		}
		
		printf("%s\n",nimSum ? "Alice" : "Bob");
	}
	return 0;
}
