#include <bits/stdc++.h>
using namespace std;

const int R = 52;
const int C = 22;
const int MAGIC = 28657; // fibo(22) or fibo(23) dunno don't care

int inve[(1 << C)];
int mask[MAGIC];
int cnt;
int r,c;
int dp[2][C + 1][MAGIC];
char s[R + 5][C + 5];

void rec(int bm,int pos){
    if(pos == c){
        mask[cnt] = bm;
        inve[bm] = cnt++;
        //printf("%d %d\n",cnt,bm);
    }
    else{
        rec(bm,pos + 1);
        if(pos + 2 <= c)
            rec(bm | (1 << pos) | (1 << (pos + 1)),pos + 2);    
    }
}

void init(){
    scanf("%d %d",&r,&c);
    //assert(r <= R && c <= C);
    for(int i = 0 ; i < r ; i++)
        scanf("%s",s[i]);
    rec(0,0);
    //printf("%d\n",cnt);        
}

bool can_place_four(int row,int col,int bm){
    if(col + 4 > c) return 0;
    if(s[row][col] == 'X' || s[row][col + 1] == 'X' || s[row][col + 2] == 'X' || s[row][col + 3] == 'X') return 0;
    if((bm & (1 << col)) != 0 || (bm & (1 << (col + 1))) != 0 || (bm & (1 << (col + 2))) != 0 || (bm & (1 << (col + 3))) != 0) return 0;
    return 1;
}

bool can_place_two(int row,int col,int bm){
    if(row + 2 > r || col + 2 > c) return 0;
    if(s[row][col] == 'X' || s[row][col + 1 ] == 'X' || s[row + 1][col] == 'X' || s[row + 1][col + 1] == 'X') return 0;
    if((bm & (1 << col)) != 0 || (bm & (1 << (col + 1))) != 0) return 0;
    return 1;
}

void solve(){
    memset(dp,-1,sizeof dp);
    int ans = 0;
    dp[0][0][inve[0]] = 0;
    for(int row = 0 ; row < r ; row++){
        int bit = row & 1;
        for(int col = 0 ; col < c ; col++)
            for(int i = 0 ; i < cnt ; i++)
                if(dp[bit][col][i] >= 0){
                    int bm = mask[i];
                    //printf("row %d col %d mask %d dp %d\n",row,col,bm,dp[bit][col][i]);
                    if(can_place_four(row,col,bm)){
                        int nmask = bm;
                        nmask = inve[nmask];
                        dp[bit][col + 4][nmask] = max(dp[bit][col + 4][nmask],dp[bit][col][i] + 1);
                    }
                    if(can_place_two(row,col,bm)){
                        int nmask = bm;
                        nmask |= (1 << col);
                        nmask |= (1 << (col + 1));
                        nmask = inve[nmask];
                        dp[bit][col + 2][nmask] = max(dp[bit][col + 2][nmask],dp[bit][col][i] + 1);
                    }
                    int nmask = bm;
                    if(nmask & (1 << col)){
                        assert((nmask & (1 << (col + 1))) != 0);
                        nmask ^= (1 << col);
                        nmask ^= (1 << (col + 1));
                        nmask = inve[nmask];
                        dp[bit][col + 2][nmask] = max(dp[bit][col + 2][nmask],dp[bit][col][i]);
                    }
                    else{
                        nmask = inve[nmask];
                        dp[bit][col + 1][nmask] = max(dp[bit][col + 1][nmask],dp[bit][col][i]);
                    }
                }
        memset(dp[bit ^ 1],-1,sizeof dp[bit ^ 1]);
        for(int i = 0 ; i < cnt ; i++)
            dp[bit ^ 1][0][i] = dp[bit][c][i];
    }
    int bit = (r & 1);
    for(int i = 0 ; i < cnt ; i++)
        ans = max(ans,dp[bit][0][i]);
    printf("%d\n",ans);
}

int main(){
    init();
    solve();
    return 0;
}
