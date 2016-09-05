#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int dp[N][N];
int nxt[N][26],prv[N][26];
char s[N];
int len;
char ans[N];
int anslen;

int solve(int l,int r){
    if(l > r) return 0;
    if(l == r) return 1;
    int &ret = dp[l][r];
    if(ret != -1) return ret;
    ret = max(solve(l + 1,r),solve(l,r - 1));
    if(s[l] == s[r])
        ret = max(ret,2 + solve(l + 1,r - 1));
    return ret;    
}

void backtrack(){
    memset(dp,-1,sizeof dp);
    anslen = solve(0,len - 1);
    int l = 0;
    int r = len - 1;
    int maks = -1;
    char ch = 0;
    int nl,nr,res;
    for(int i = 0 ; i < 26 ; i++){
        nl = 0;
        while(nl < len && s[nl] != i + 'a') nl++;
        nr = len - 1;
        while(nr >= 0 && s[nr] != i + 'a') nr--;
        res = solve(nl,nr);
        if(res > maks){
            maks = res;
            l = nl;
            r = nr;
            ch = i;
        }
    }
    ans[0] = ans[anslen - 1] = ch + 'a';
    for(int i = 1 ; i < (anslen + 1) / 2 ; i++){
        maks = -1;
        ch = 0;
        for(int j = 0 ; j < 26 ; j++){
            nl = nxt[l][j];
            nr = prv[r][j];
            res = solve(nl,nr);
            if(res > maks){
                maks = res;
                ch = j;
            }
        }
        //printf("i %d ch %c maks %d\n",i,ch + 'a',maks);
        ans[i] = ans[anslen - i - 1] = ch + 'a';
        l = nxt[l][ch];
        r = prv[r][ch];
    }  
    ans[anslen] = '\0';
    printf("%s\n",ans);          
}

void init(){
    len = strlen(s);
    for(int i = 0 ; i < 26 ; i++)
        prv[0][i] = -1000000000;
    for(int i = 1 ; i < len ; i++){
        for(int j = 0 ; j < 26 ; j++)
            prv[i][j] = prv[i - 1][j];
        prv[i][s[i - 1] - 'a'] = i - 1;    
    } 
    for(int i = 0 ; i < 26 ; i++)
        nxt[len - 1][i] = 1000000000;
    for(int i = len - 2 ; i >= 0 ; i--){
        for(int j = 0 ; j < 26 ; j++)
            nxt[i][j] = nxt[i + 1][j];
        nxt[i][s[i + 1] - 'a'] = i + 1;    
    }       
}

int main(){
    while(scanf("%s",s) != EOF){
        init();
        backtrack();
    }
    return 0;
}
