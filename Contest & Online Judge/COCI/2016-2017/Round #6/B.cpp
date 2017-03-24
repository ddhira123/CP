#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

int arr[N];
int n, k;

int main() {
	scanf("%d %d",&n,&k);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d", arr + i);
	}

	int lst = 1;
	int ret = 0;

	for(int i = 2 ; i <= n ; i++) {
		if(arr[i] == 1) {
			lst = i;
		} else {
			if(i-lst == k) {
				lst = i;
				ret++;
			}
		}
	}

	printf("%d\n", ret);
	return 0;
}