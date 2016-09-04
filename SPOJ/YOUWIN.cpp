#include <bits/stdc++.h>
using namespace std;

const int N = 18;
const int INF = (int)1e9;

int dp[N][1 << N];
char s[N + 5];
int len;

int getDistance(char a,char b) {
	if(a > b) swap(a,b);
	int dis = b - a;
	return min(dis,26 - dis);
}

int getOnBit(int a,int b) {
	return __builtin_popcount(a ^ b);
}

int solve(int last,int mask) {
	if(mask == (1 << len) - 1)
		return 0;
	int &ret = dp[last][mask];
	if(ret != -1) return ret;
	ret = INF;	
	for(int i = 0 ; i < len ; i++)
		if((mask & (1 << i)) == 0) {
			int temp = mask ^ (1 << last);
			int a = temp & ((1 << i) - 1);
			int b = temp & ((1 << last) - 1);
			ret = min(ret,1 + getOnBit(a,b) + (int)(last > i) + getDistance(s[i],s[last]) + solve(i,mask | (1 << i)));
		}
	//printf("%d %d %d\n",last,mask,ret);	
	return ret;	
}

int main() {
	while(scanf("%s",s) && s[0] != '0') {
		len = strlen(s);
		for(int i = 0 ; i < len ; i++)
			for(int j = 0 ; j < (1 << len) ; j++)
				dp[i][j] = -1;
		int ans = INF;
		for(int i = 0 ; i < len ; i++) {
			int tot = 1 + getDistance('A',s[i]) + solve(i,1 << i);
			ans = min(ans,tot);
			//cout << i << " " << tot << endl;
		}	
		printf("%d\n",ans);			
	}
	return 0;
}
