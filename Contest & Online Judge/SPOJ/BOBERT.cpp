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

const int MAXN = 100005;
const int LOG = 20;

int len[LOG + 5];
int total[(1 << LOG) + 5];
LL dp[(1 << LOG) + 5];
int arr[MAXN];

int prev_maks[LOG + 1][MAXN],next_maks[LOG + 1][MAXN];
int prev_mins[LOG + 1][MAXN],next_mins[LOG + 1][MAXN];

int n,k;

void Read(){
    //scanf("%d",&n);
    n = io();
    for(int i = 0 ; i < n ; i++){
        //scanf("%d",&arr[i]);
        arr[i] = io();
    }    
    //scanf("%d",&k);
    k = io();
    for(int i = 0 ; i < k ; i++){
        //scanf("%d",&len[i]);
        len[i] = io();
        total[1 << i] = len[i];
    }    
}

void Precompute(){
    for(int i = 0 ; i < (1 << k) ; i++)
        total[i] = total[i & -i] + total[i - (i & -i)];
    for(int i = 0 ; i < k ; i++){
        int cnt = len[i];
        for(int j = 0 ; j < n ; j++){
            if(cnt == len[i]){
                prev_maks[i][j] = prev_mins[i][j] = arr[j];
                cnt = 0;
            }
            else{
                prev_maks[i][j] = max(arr[j],prev_maks[i][j - 1]);
                prev_mins[i][j] = min(arr[j],prev_mins[i][j - 1]);
            }
            cnt++;
        }
        if(cnt == len[i]) cnt = 0;
        cnt--;
        next_maks[i][n] = -INF;
        next_mins[i][n] = INF;
        for(int j = n - 1 ; j >= 0 ; j--){
            if(cnt == -1){
                next_maks[i][j] = next_mins[i][j] = arr[j];
                cnt = len[i] - 1;
            }
            else{
                next_maks[i][j] = max(arr[j],next_maks[i][j + 1]);
                next_mins[i][j] = min(arr[j],next_mins[i][j + 1]);
            }
            cnt--;
        }
    }    
}

LL Solve(){
    for(int i = 0 ; i < (1 << k) ; i++)
        dp[i] = -INFLL;
    dp[0] = 0;
    for(int i = 0 ; i < (1 << k) ; i++){
        int start = total[i];
        //for(int j = 0 ; j < k ; j++)
            //if(i & (1 << j))
                //start += len[j];
        for(int j = 0 ; j < k ; j++)
            if((i & (1 << j)) == 0){
                int maks = max(next_maks[j][start],prev_maks[j][start + len[j] - 1]);
                int mins = min(next_mins[j][start],prev_mins[j][start + len[j] - 1]);
                dp[i | (1 << j)] = max(dp[i | (1 << j)],dp[i] + (LL)(len[j])*(LL)(maks - mins));
            }
        //printf("%d -> START %d DP %lld\n",i,total[i],dp[i]);    
    }        
    return dp[(1 << k) - 1];        
}

int main(){
    Read();
    Precompute();
    printf("%lld\n",Solve());
    //puts("ganteng");
    return 0;
}
