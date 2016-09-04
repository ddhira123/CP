#include <bits/stdc++.h>
using namespace std;

const int N = 5000;

char s[N + 5];
char isPalin[N + 1][N + 1];
int dp[N + 1][N + 1];
int q;

char isPalindrome(int l,int r) {
	if(l >= r) return 1;
	char &ret = isPalin[l][r];
	if(ret != -1) return ret;
	return ret = (s[l] != s[r]) ? 0 : isPalindrome(l + 1,r - 1);
}

int solve(int l,int r) {
	if(l == r) return 1;
	if(l + 1 == r) return 2 + (s[l] == s[r]);
	int &ret = dp[l][r];
	if(ret != -1) return ret;
	
	ret = solve(l + 1,r) + solve(l,r - 1) - solve(l + 1,r - 1);
	ret += isPalindrome(l,r);
	
	return ret;
}

int main() {
	memset(dp,-1,sizeof dp);
	memset(isPalin,-1,sizeof isPalin);
	
	scanf("%s",s);
	scanf("%d",&q);
	
	while(q--) {
		int l,r;
		scanf("%d %d",&l,&r);
		printf("%d\n",solve(l - 1,r - 1));
	}
	return 0;
}