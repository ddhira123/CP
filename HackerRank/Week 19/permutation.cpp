#include <bits/stdc++.h>
using namespace std;

void generatePermutation(int x) {
	int arr[x];
	for(int i = 0 ; i < x ; i++) arr[i] = i + 1;
	int maks = -1;
	do {
		int mins = (int)1e9;
		for(int i = 0 ; i + 1 < x ; i++)
			mins = min(mins,abs(arr[i] - arr[i + 1]));
		maks = max(maks,mins);
	}while(next_permutation(arr,arr + x));

	sort(arr,arr + x);
	int cnt = 0;
	int m2 = -1;
	do {
		int mins = (int)1e9;
		for(int i = 0 ; i + 1 < x ; i++)
			mins = min(mins,abs(arr[i] - arr[i + 1]));
		if(maks == mins) {
			int temp = -1;
			for(int i = 0 ; i < x ; i++) {
				printf("%d ",arr[i]);
				if(i + 1 < x)
					temp = max(temp,abs(arr[i] - arr[i + 1]));
			}
			m2 = max(m2,temp);
			puts("");
			cnt++;
		}	
	}while(next_permutation(arr,arr + x));
	printf("X %d MAKS %d CNT %d M2 %d\n",x,maks,cnt,m2);
}

int main() {
	for(int i = 2 ; i <= 15 ; i++) {
		generatePermutation(i);
		getchar();
	}
	return 0;
}