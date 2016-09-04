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

const int M = 125;
const int N = 85;

bool blocked[M];
vector<pii> adj[N];
int n,m,tc;
int prev[N];
int num[N],lo[N];
int cnt;

void Reset(){
    for(int i = 1 ; i <= n ; i++){
        prev[i] = 0;
        num[i] = lo[i] = -1;
    }
}

int Tarjan(int now){
    num[now] = lo[now] = cnt++;
    int res = 0;
    for(int i = 0 ; i < adj[now].size() ; i++){
        int idx = adj[now][i].se;
        int nxt = adj[now][i].fi;
        if(blocked[idx]) continue;
        if(num[nxt] == -1){
            prev[nxt] = now;
            res += Tarjan(nxt);
            if(lo[nxt] > num[now]){
                res++;
                blocked[idx] = 1;
            }
            lo[now] = min(lo[now],lo[nxt]);
        }
        else if(prev[now] != nxt)
            lo[now] = min(lo[now],num[nxt]);
    }
    return res;
}

void Read(){
    scanf("%d %d",&n,&m);
    for(int i = 1 ; i <= n ; i++)
        adj[i].clear();
    for(int i = 0 ; i < m ; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        adj[a].pb(mp(b,i));
        adj[b].pb(mp(a,i));
    }
}

ULL Solve(){
    for(int i = 0 ; i < m ; i++)
        blocked[i] = 0;
    ULL ans;
    Reset();
    for(int i = 1 ; i <= n ; i++)  
        if(num[i] == -1){
            ans = Tarjan(i);
            cnt = 0;
        }    
    ans = 1;        
    for(int i = 1 ; i <= n ; i++)
        for(int j = 0 ; j < adj[i].size() ; j++){
            int idx = adj[i][j].se;
            if(!blocked[idx]){
                blocked[idx] = 1;
                Reset();
                ans *= (ULL)(Tarjan(i) + 1);
                //printf("%d %d\n",i,idx);
                cnt = 0;
            }
        }           
    return ans;    
}

int main(){
    scanf("%d",&tc);
    for(int T = 1 ; T <= tc ; T++){
        Read();
        printf("Case %d: %llu\n",T,Solve());
    }
    //puts("ganteng");
    return 0;
}

