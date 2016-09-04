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
#define MOD 100000007LL
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

const int N = 405;

LL dp[N][3][N / 2];
LL tmp[N][3][N / 2];
vector<int> adj[N];
int n,m,k,tc;

void Reset(){
    for(int i = 1 ; i <= n ; i++){
        adj[i].clear();
        for(int j = 0 ; j < 3 ; j++)
            for(int l = 0 ; l <= k && l <= n / 2 ; l++)
                dp[i][j][l] = tmp[i][j][l] = 0;
        dp[i][0][0] = 1;
        dp[i][1][1] = 1;        
    }
}

void Store(int pos){
    //memset(tmp,0,sizeof tmp);
    int i;
    for(i = 0 ; i <= k && dp[pos][0][i] > 0 ; i++){
        tmp[pos][0][i] = dp[pos][0][i];
        dp[pos][0][i] = 0;
    }
    tmp[pos][0][i] = 0;
    for(i = 1 ; i <= k && dp[pos][1][i] + dp[pos][2][i] > 0 ; i++)
        for(int j = 1 ; j <= 2 ; j++){
            tmp[pos][j][i] = dp[pos][j][i];
            dp[pos][j][i] = 0;
        }
    tmp[pos][1][i] = tmp[pos][2][i] = 0;    
}

void DFS(int pos,int prev){
    for(int i = 0 ; i < adj[pos].size() ; i++){
        int nxt = adj[pos][i];
        if(nxt == prev) continue;
        DFS(nxt,pos);
        Store(pos);
        for(int i = 0 ; i <= k && tmp[pos][0][i] > 0 ; i++) // pos gak dipake 
            for(int j = 0 ; j + i <= k && dp[nxt][0][j] + dp[nxt][2][j] > 0 ; j++)
                dp[pos][0][i + j] = (dp[pos][0][i + j] + tmp[pos][0][i] * (dp[nxt][0][j] + dp[nxt][2][j])) % MOD;
        
        for(int i = 1 ; i <= k && tmp[pos][1][i] > 0 ; i++) // pos dipake ujung bawah
            for(int j = 0 ; j + i <= k && dp[nxt][0][j] + dp[nxt][2][j] > 0 ; j++)
                dp[pos][1][i + j] = (dp[pos][1][i + j] + tmp[pos][1][i] * (dp[nxt][0][j] + dp[nxt][2][j])) % MOD;
        
        for(int i = 0 ; i <= k && tmp[pos][0][i] > 0 ; i++) // bikin pos dipake
            for(int j = 1 ; j + i <= k && dp[nxt][1][j] > 0 ; j++)
                dp[pos][2][i + j] = (dp[pos][2][i + j] + tmp[pos][0][i] * dp[nxt][1][j]) % MOD;
       
        for(int i = 1 ; i <= k && tmp[pos][2][i] > 0 ; i++) // udah dibikin pasangan
            for(int j = 0 ; j + i <= k && dp[nxt][0][j] + dp[nxt][2][j] > 0 ; j++)
                dp[pos][2][i + j] = (dp[pos][2][i + j] + tmp[pos][2][i] * (dp[nxt][0][j] + dp[nxt][2][j])) % MOD;                         
    }
}

int main(){
    scanf("%d",&tc);
    while(tc--){
        scanf("%d %d %d",&n,&m,&k);
        Reset();
        for(int i = 1 ; i <= m ; i++){
            int a,b;
            scanf("%d %d",&a,&b);
            adj[a].pb(b);
            adj[b].pb(a);
        }
        int ans = 0;
        if(n >= k * 2){
            DFS(1,0);
            ans = dp[1][0][k] + dp[1][2][k];
            if(ans >= MOD) ans -= MOD;
            /*for(int i = 1 ; i <= n ; i++)
                for(int j = 0 ; j < 3 ; j++)
                    for(int l = 0 ; l <= k ; l++)
                        printf("DP %d %d %d : %lld\n",i,j,l,dp[i][j][l]);*/
        }
        printf("%d\n",ans);
    }
    //puts("ganteng");
    return 0;
}

