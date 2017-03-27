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

const int N = 100005;

vector<int> adj[N];
LL ans[N];
int low[N],num[N];
int sz[N];
int prev[N];
int cnt;
int n,m;

void Tarjan(int now){
    num[now] = low[now] = cnt++;
    sz[now] = 1;
    int sum = 0;
    for(int i = 0 ; i < adj[now].size() ; i++){
        int nxt = adj[now][i];
        if(num[nxt] == -1){
            prev[nxt] = now;
            Tarjan(nxt);
            sz[now] += sz[nxt];
            if(low[nxt] >= num[now]){
                ans[now] += (LL)(n - 1 - sz[nxt]) * (LL)sz[nxt];
                sum += sz[nxt];
            }
            low[now] = min(low[now],low[nxt]);
        }
        else if(prev[now] != nxt)
            low[now] = min(low[now],num[nxt]);
    }
    ans[now] += (LL)(n - 1 - sum) * (LL)sum;
}

void Init(){
    scanf("%d %d",&n,&m);
    for(int i = 1 ; i <= n ; i++){
        ans[i] = 2 * (n - 1);
        num[i] = -1;
    }
    for(int i = 1 ; i <= m ; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        adj[a].pb(b);
        adj[b].pb(a);
    }
}

int main(){
    Init();
    Tarjan(1);
    assert(sz[1] == n);
    for(int i = 1 ; i <= n ; i++)
        printf("%lld\n",ans[i]);
    //puts("ganteng");
    return 0;
}
