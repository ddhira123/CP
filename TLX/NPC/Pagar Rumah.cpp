#include <bits/stdc++.h>
using namespace std;

const int N = 5005;

int arr[N];

int rec(int l,int r,int maks){
	if(r < l) return 0;
	int res = 0;
	int mins = (int)1e9;
	for(int i = l ; i <= r ; i++)
		mins = min(mins,arr[i]);	
	res = mins - maks;
	for(int i = l ; i <= r ; ){
		if(arr[i] == mins)
			i++;
		else{
			int j = i;
			while(j <= r && arr[j] > mins) j++;
			res += rec(i,j - 1,mins);
			i = j;
		}	
	}
	res = min(res,r - l + 1);
	return res;	
}

int main(){
	int n;
	cin >> n;
	for(int i = 0 ; i < n ; i++)
		cin >> arr[i];
	cout << rec(0,n - 1,0) << endl;	
	return 0;
}
