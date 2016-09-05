#include <bits/stdc++.h>
using namespace std;

const int N = 10000;
const int LEN = 21;
const int LETTER = 26;

struct node{
	bool en;
	int nxt[LETTER];
	
	void reset(){
		en = 0;
		memset(nxt,-1,sizeof nxt);
	}
};

node trie[N * LEN];
int dp[N * LEN][2];
char s[LEN + 5];
int saiz;

void add(){
	int cur = 0;
	int len = strlen(s);
	for(int i = 0 ; i < len ; i++){
		int edge = s[i] - 'A';
		if(trie[cur].nxt[edge] == -1){
			trie[cur].nxt[edge] = ++saiz;
			trie[saiz].reset();
		}
		cur = trie[cur].nxt[edge];
	}
	trie[cur].en = 1;
}

void dfs(int pos){
	int sum = 0;
	for(int i = 0 ; i < LETTER ; i++)
		if(trie[pos].nxt[i] != -1){
			dfs(trie[pos].nxt[i]);
			sum += dp[trie[pos].nxt[i]][0];
		}
	//kalo ini udah kematch
	dp[pos][1] = sum;
	dp[pos][0] = sum;
	//coba match
	if(trie[pos].en)
		for(int i = 0 ; i < LETTER ; i++)
			if(trie[pos].nxt[i] != -1){
				int nex = trie[pos].nxt[i];
				if(trie[nex].en)
					dp[pos][0] = max(dp[pos][0],1 + sum - dp[nex][0] + dp[nex][1]);
			}	
}

int main(){
	int tc;
	scanf("%d",&tc);
	for(int t = 1 ; t <= tc ; t++){
		int n;
		scanf("%d",&n);
		saiz = 0;
		trie[0].reset();
		for(int i = 0 ; i < n ; i++){
			scanf("%s",s);
			add();
		}
		dfs(0);
		printf("Case #%d: %d\n",t,dp[0][0]);
	}
	return 0;
}
