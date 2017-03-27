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

const int N = 3005;

int dp[N][2][N];
int tmp[N][2][N];
int tc,n,m,k;
vector<pii> adj[N];
vector<pii> chld[N];
int sz[N];

void Clear(){
    for(int i = 1 ; i <= n ; i++){
        for(int j = 0 ; j < 2 ; j++)
            for(int l = 0 ; l <= k && l <= sz[i] ; l++)
                dp[i][j][l] = INF;
        dp[i][0][0] = 0;
        dp[i][1][1] = 0;     
    }
}

void Build(int pos,int prev){
    sz[pos] = 1;
    for(int i = 0 ; i < adj[pos].size() ; i++){
        int nxt = adj[pos][i].fi;
        if(nxt != prev){
            //printf("%d -> %d\n",pos,nxt);
            chld[pos].pb(adj[pos][i]);
            Build(nxt,pos);
            sz[pos] += sz[nxt];
        }
    }
}

void Reset(int pos){
    for(int i = 0 ; i < 2 ; i++)
        for(int j = 0 ; j <= k && j <= sz[pos] ; j++){
            tmp[pos][i][j] = dp[pos][i][j];
            dp[pos][i][j] = INF;
        }   
}

void DFS(int pos){
    if(chld[pos].empty()){
    }
    else{
        for(int i = 0 ; i < chld[pos].size() ; i++){
            int nxt = chld[pos][i].fi;
            int cost = chld[pos][i].se;
            DFS(nxt);
            Reset(pos);
            for(int j = 1 ; j <= k && j <= sz[pos] ; j++){ // dimakan bos
                if(tmp[pos][1][j] == INF)
                    break;
                for(int l = 0 ; l <= sz[nxt] && l + j <= k ; l++){
                    dp[pos][1][j + l] = min(dp[pos][1][j + l],tmp[pos][1][j] + dp[nxt][0][l]);
                    dp[pos][1][j + l] = min(dp[pos][1][j + l],tmp[pos][1][j] + dp[nxt][1][l] + cost);
                }
            }    
            for(int j = 0 ; j <= k && j <= sz[pos] ; j++){
                if(tmp[pos][0][j] == INF)
                    break;
                for(int l = 0 ; l <= sz[nxt] && l + j <= k ; l++){
                    dp[pos][0][j + l] = min(dp[pos][0][j + l],tmp[pos][0][j] + dp[nxt][1][l]);
                    dp[pos][0][j + l] = min(dp[pos][0][j + l],tmp[pos][0][j] + dp[nxt][0][l] + cost * (m == 2 ? 1 : 0));
                }          
            }                 
        }
    }
    //printf("NOW %d\n",pos);
    //for(int i = 0 ; i < 2 ; i++)
    //    for(int j = 0 ; j <= k ; j++)
    //        printf("%d %d -> %d\n",i,j,dp[pos][i][j]);
}

int main(){
    scanf("%d %d %d",&n,&m,&k);
    for(int i = 1 ; i < n ; i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        adj[a].pb(mp(b,c));
        adj[b].pb(mp(a,c));
    }
    int ans = -1;
    if(k + m - 1 <= n){
        Build(1,0);
        Clear();
        DFS(1);
        ans = dp[1][1][k];
    }
    printf("%d\n",ans);
    //puts("ganteng");
    return 0;
}
