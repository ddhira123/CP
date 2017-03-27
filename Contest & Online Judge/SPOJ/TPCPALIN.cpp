#include <bits/stdc++.h>
using namespace std;

const int N = 501;
const int MOD = 3210121;

int dp[N][N][N];
int dpPalin[2][N][N];

char s[2][N + 5];
int len[2];

int isPalin(int id,int lef,int rig) {
	if(lef >= rig) return 1;
	
	int &ret = dpPalin[id][lef][rig];
	if(ret != -1) return ret;
	
	if(s[id][lef] == s[id][rig])
		ret = isPalin(id,lef + 1,rig - 1);
	else
		ret = 0;	
	return ret;
}

int solve(int prefixOne,int suffixOne,int prefixTwo) {
	int suffixTwo = len[1] + len[0] - suffixOne - 2 - prefixOne - prefixTwo;
	
	if(prefixOne > suffixOne) 
		return isPalin(1,prefixTwo,suffixTwo);
	else if(prefixTwo > suffixTwo)
		return isPalin(0,prefixOne,suffixOne);
	
	int &ret = dp[prefixOne][suffixOne][prefixTwo];
	if(ret != -1) return ret;
	
	ret = 0;
	//pasang 0 0
	if(prefixOne < suffixOne && s[0][prefixOne] == s[0][suffixOne])
		ret += solve(prefixOne + 1,suffixOne - 1,prefixTwo);
	
	//pasang 0 1
	if(s[0][prefixOne] == s[1][suffixTwo])
		ret += solve(prefixOne + 1,suffixOne,prefixTwo);
	
	//pasang 1 0
	if(s[0][suffixOne] == s[1][prefixTwo])
		ret += solve(prefixOne,suffixOne - 1,prefixTwo + 1);
	
	//pasang 1 1
	if(prefixTwo < suffixTwo && s[1][prefixTwo] == s[1][suffixTwo])
		ret += solve(prefixOne,suffixOne,prefixTwo + 1);
	
	ret %= MOD;
	return ret;						
}

void reset() {
	for(int i = 0 ; i < len[0] ; i++)
		for(int j = i ; j < len[0] ; j++)
			for(int k = 0 ; k < len[1] ; k++)
				dp[i][j][k] = -1;
	
	for(int i = 0 ; i < 2 ; i++)
		for(int j = 0 ; j < len[i] ; j++)
			for(int k = j ; k < len[i] ; k++)
				dpPalin[i][j][k] = -1;			
}

int main() {
	for(int i = 0 ; i < 2 ; i++) {
		scanf("%s",s[i]);
		len[i] = strlen(s[i]);
	}
	
	if(len[1] < len[0]) {
		swap(len[0],len[1]);
		swap(s[0],s[1]);
	}
	
	//memset(dp,-1,sizeof dp);
	//memset(dpPalin,-1,sizeof dpPalin);
	reset();
	
	printf("%d\n",solve(0,len[0] - 1,0));
	return 0;
}