#include<bits/stdc++.h>
using namespace std;

int arr[6];

bool isPositive(int &x,int val) {
	x += val;
	bool ok = 1;
	if(arr[0] + arr[1] + arr[2] + arr[3] < 0) ok = 0;
	if(arr[0] + arr[1] + arr[5] < 0) ok = 0;
	if(arr[0] + arr[4] + arr[3] < 0) ok = 0;
	x -= val;
	return ok;
}

int main() {
	for(int i = 0 ; i < 6 ; i++) scanf("%d",arr + i);
	int lo = 0,hi = 1000;
	while(lo < hi) {
		int mid = (lo + hi) / 2;
		bool yes = 0;
		for(int i = 0 ; i < 6 ; i++)
			yes |= isPositive(arr[i],mid);
		if(yes)
			hi = mid;
		else 
			lo = mid + 1;
	}	
	if(lo > 100) lo = -1;
	printf("%d\n",lo);	
	return 0;
}