#include <bits/stdc++.h>
using namespace std;

const int N = 20005;

pair<int,int> arr[N];
int n,tc;

int main(){
	scanf("%d",&tc);
	for(int t = 1 ; t <= tc ; t++){
		scanf("%d",&n);
		for(int i = 0 ; i < n ; i++)
			scanf("%d %d",&arr[i].first,&arr[i].second);
		sort(arr,arr + n);
		int ymaks = 0;
		int median = arr[n / 2].first;
		int tot = 0;
		for(int i = 0 ; i < n ; i++){
			tot += abs(median - arr[i].first);
			ymaks = max(ymaks,arr[i].second);
		}	
		tot += ymaks;
		printf("Kasus #%d: %d\n",t,tot);
	}
	return 0;
}
