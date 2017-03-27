#include <bits/stdc++.h>
using namespace std;

const int K = 205;

vector<int> v[K];
long long compressed[K][K];
int n,k;
long long dp[K][K];

int add(int x,int y){
	x += y;
	if(x >= k) x -= k;
	return x;
}

long long solve(int pos,int modulo){
	if(pos == k){
		if(modulo == 0)
			return 0;
		return (long long)-1e18;	
	}
	long long &ret = dp[pos][modulo];
	if(ret != -1) return ret;
	ret = (long long)-1e18;
	for(int i = 0 ; i < k ; i++)
		if(compressed[pos][i] != -1)
			ret = max(ret,compressed[pos][i] + solve(pos + 1,add(modulo,k - i)));
	return ret;		
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i = 0 ; i < n ; i++){
		int x;
		scanf("%d",&x);
		v[x % k].push_back(x);
	}
	memset(compressed,-1,sizeof compressed);
	for(int i = 0 ; i < k ; i++){
		sort(v[i].begin(),v[i].end());
		long long sum = 0;
		int modulo = 0;
		compressed[i][0] = 0;
		for(int j = (int)v[i].size() - 1 ; j >= 0 ; j--){
			sum += v[i][j];
			modulo = add(modulo,i);
			compressed[i][modulo] = max(sum,compressed[i][modulo]);
		}
	}
	memset(dp,-1,sizeof dp);
	for(int i = 0 ; i < k ; i++){
		long long res = solve(0,i);
		if(res <= 0) res = -1;
		printf("%lld%c",res,i + 1 == k ? '\n' : ' ');
	}
	return 0;
}