#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <vector>
#include <bitset>
#include <cassert>
//Because defining using namespace std is too mainstream
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;
typedef pair<string,string> pss;
typedef pair<int,double> pid;
typedef pair<int,LL> pil;
typedef pair<LL,LL> pll;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SYNC ios_base::sync_with_stdio(false)
#define TIE cin.tie(0)
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL
#define DEBUG puts("DEBUG")

#ifdef _WIN32
    #define getchar_unlocked getchar
#endif

#define g getchar_unlocked

int dx8[8]={-1,-1,0,1,1,1,0,-1},dx4[4]={-1,0,1,0};
int dy8[8]={0,-1,-1,-1,0,1,1,1},dy4[4]={0,-1,0,1};

inline void open(string name){
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}

inline void close(){
    fclose(stdin);
    fclose(stdout);
}

inline int io(){
    register char c;
    while(1){
        c = g();
        if(c != '\n' && c != ' ') break;
    }
    int res = 0, sign = 1;
    if(c=='-') sign = -1;
    else       res = c-'0';
    while(1){
        c = g();
        if(c == ' ' || c == '\n' || c == EOF) break;
        res = (res << 3) + (res << 1) + c - '0';
    }
    return res * sign;
}

///////////////////////////////////////////////////
//////            End of Template            /////
/////////////////////////////////////////////////

const int M = 12;
const int N = 130;
const int MAXM = 180000;

int item[MAXM];
int dp[MAXM];
int pangkat[M];
int n,m;
char s[N][M];

/*int solve(int mask){
    if(item[mask] <= 1)
        return 0;
    int &ret = dp[mask];
    if(ret != -1)
        return ret;
    ret = INF;
    int lol = mask;
    for(int i = 0 ; i < m ; i++){
        if(lol % 3 == 2){
            int next_mask = mask - pangkat[i];
            if(item[next_mask] > 0 && item[next_mask] < item[mask]){
                int ans1 = solve(next_mask);
                int ans2 = solve(next_mask - pangkat[i]);
                ret = min(ret,max(ans1,ans2));
            } 
        }
        lol /= 3;
    }        
    ret++;
    return ret;
}*/



void rec(int idx,int pos,int mask){
    if(pos == m)
        item[mask]++;
    else{
        rec(idx,pos + 1,mask + 2 * pangkat[pos]);       
        rec(idx,pos + 1,mask + (int)(s[idx][pos] - '0') * pangkat[pos]);
    }    
}

void reset(int pos,int mask){
    if(pos == m)
        item[mask] = 0;
    else{
        reset(pos + 1,mask + 2 * pangkat[pos]);
        reset(pos + 1,mask + 1 * pangkat[pos]);
        reset(pos + 1,mask + 0 * pangkat[pos]);
    }   
}

int DP(){
    for(int mask = 0 ; mask < pangkat[m] ; mask++)
        if(item[mask] <= 1)
            dp[mask] = 0;
        else{
            dp[mask] = INF;
            int lol = mask;
            for(int i = 0 ; i < m ; i++){
                if(lol % 3 == 2){
                    int next_mask = mask - pangkat[i];
                    if(item[next_mask] > 0 && item[next_mask] < item[mask]){
                        dp[mask] = min(dp[mask],max(dp[next_mask],dp[next_mask - pangkat[i]]));
                    } 
                }
                lol /= 3;
            }
            dp[mask]++;   
        }   
   return dp[pangkat[m] - 1];      
}

int main(){
    pangkat[0] = 1;
    for(int i = 1 ; i < M ; i++)
        pangkat[i] = pangkat[i - 1] * 3;
    scanf("%d %d",&m,&n);
    while(m | n){
        //memset(item,0,sizeof item);
        //for(int i = 0 ; i < pangkat[m] ; i++)
        //    dp[i] = -1;
        for(int i = 0 ; i < n ; i++){
            scanf("%s",s[i]);
            rec(i,0,0);
        }        
        //printf("%d\n",solve(pangkat[m] - 1));
        printf("%d\n",DP());
        reset(0,0);
        scanf("%d %d",&m,&n);
    }
    //puts("ganteng");
    return 0;
}
