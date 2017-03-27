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
const int LOG = 17;

vector<int> adj[N];
int num[N],low[N];
int prev[N];

vector<pii> chld[N];
pii anc[N][LOG];
int depth[N];

int n,m,q,tc;
int cnt;

void Tarjan(int now){
    num[now] = low[now] = cnt++;
    for(int i = 0 ; i < adj[now].size() ; i++){
        int nxt = adj[now][i];
        if(num[nxt] == -1){
            prev[nxt] = now;
            Tarjan(nxt);
            int val = 0;
            if(low[nxt] > num[now])
                val = 1;
            chld[now].pb(mp(nxt,val));
            low[now] = min(low[now],low[nxt]);    
        }
        else if(prev[now] != nxt)
            low[now] = min(low[now],num[nxt]);
    }
}

void Build(int pos,int pre,int val){
    anc[pos][0] = mp(pre,val);
    for(int i = 1 ; (1 << i) <= depth[pos] ; i++){
        pii par = anc[pos][i - 1];
        pii gpar = anc[par.fi][i - 1];
        anc[pos][i].fi = gpar.fi;
        anc[pos][i].se = gpar.se + par.se; 
    }
}

void DFS(int now){
    for(int i = 0 ; i < chld[now].size() ; i++){
        int nxt = chld[now][i].fi;
        depth[nxt] = depth[now] + 1;
        Build(nxt,now,chld[now][i].se);
        DFS(nxt);
    }
}

int LCA(int u,int v){
    if(depth[u] < depth[v]) swap(u,v);
    int diff = depth[u] - depth[v];
    int ans = 0;
    for(int i = 0 ; (1 << i) <= diff ; i++)
        if(diff & (1 << i)){
            ans += anc[u][i].se;
            u = anc[u][i].fi;
            diff ^= (1 << i);
        }
    if(u == v) return ans;
    int lg = 0;
    while((1 << lg) <= depth[u]) lg++;
    lg--;
    for(int i = lg ; i >= 0 ; i--)
        if((1 << i) <= depth[u] && anc[u][i].fi != anc[v][i].fi){
            ans += anc[u][i].se;
            ans += anc[v][i].se;
            u = anc[u][i].fi;
            v = anc[v][i].fi;
        }    
    assert(anc[u][0].fi == anc[v][0].fi);
    ans += anc[u][0].se;
    ans += anc[v][0].se;
    return ans;    
}

void Init(){
    //scanf("%d %d",&n,&m);
    n = io(); m = io();
    cnt = 0;
    for(int i = 1 ; i <= n ; i++){
        adj[i].clear();
        chld[i].clear();
        num[i] = -1;
    }
    for(int i = 1 ; i <= m ; i++){
        int a,b;
        //scanf("%d %d",&a,&b);
        a = io(); b = io();
        adj[a].pb(b);
        adj[b].pb(a);
    }
    Tarjan(1);
    DFS(1);
}

void Solve(){
    //scanf("%d",&q);
    q = io();
    while(q--){
        int a,b;
        //scanf("%d %d",&a,&b);
        a = io(); b = io();
        printf("%d\n",LCA(a,b));
    }
}

int main(){
    //scanf("%d",&tc);
    tc = io();
    for(int t = 1 ; t <= tc ; t++){
        Init();
        printf("Case %d:\n",t);
        Solve();
    }
    //puts("ganteng");
    return 0;
}
