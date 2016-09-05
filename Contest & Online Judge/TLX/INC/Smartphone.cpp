#include <bits/stdc++.h>
using namespace std;

int main(){
	int tc;
	scanf("%d",&tc);
	for(int t = 1 ; t <= tc ; t++){
		int n;
		int sum = 0;
		scanf("%d",&n);
		for(int i = 0 ; i < n ; i++){
			int x;
			scanf("%d",&x);
			sum += x;
		}
		int ans = 0;
		if(sum <= 16000)
			ans = 16;
		else if(sum <= 32000)
			ans = 32;
		else if(sum <= 64000)
			ans = 64;
		else
			ans = 128;
		printf("Case #%d: %dGB\n",t,ans);				
	}
	return 0;
}
