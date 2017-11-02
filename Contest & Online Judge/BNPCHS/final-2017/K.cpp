#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int arr[N];
int n;

int main() {
	int t; scanf("%d", &t);
	for(int tc = 1 ; tc <= t ; tc++) {
		scanf("%d", &n);;
		for(int i = 0 ; i < n ; i++) {
			scanf("%d", arr + i);
		}

		sort(arr, arr + n);
		int ret = arr[n-1] - arr[0];
		int tot = -ret;

		for(int j = 1 ; j < n ; j++) {
			int temp = tot;
			temp -= (arr[j-1] - arr[j]);
			if(j+1 < n) {
				temp -= (arr[j] - arr[j+1]);
				temp += (arr[j-1] - arr[j+1]);
			}
			temp += (arr[j] - arr[0]);

			ret = min(ret, abs(temp));
		}

		printf("Kasus #%d: %d\n", tc, ret);
	}
	return 0;
}