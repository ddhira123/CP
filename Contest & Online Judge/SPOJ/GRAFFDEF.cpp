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
#include <stack>
#include <vector>
#include <bitset>
#include <cassert>
#define makmu using
#define ndasmu namespace
#define gundulmu std

makmu ndasmu gundulmu;

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
  c=g();
  if(c!='\n' && c!=' ') break;
 }
 int res=0,sign=1;
 if(c=='-') sign=-1;
 else       res=c-'0';
 while(1){
  c=g();
  if(c==' ' || c=='\n' || c==EOF) break;
  res=(res<<3)+(res<<1)+c-'0';
 }
 return res*sign;
}

///////////////////////////////////////////////////
//////            End of Template            /////
/////////////////////////////////////////////////

const int MAXN = 100005;

int num[MAXN], low[MAXN];
int par[MAXN];
int pset[MAXN], sz[MAXN];
vector<int> adj[MAXN];
int cnt;
int n,m;
LL ans;

inline void Reset(){
 for(int i = 1 ; i <= n ; i++)
  pset[i] = i, sz[i] = 1, num[i] = -1;
}

int finds(int x){
 return x == pset[x] ? x : pset[x] = finds(pset[x]);
}

inline void uni(int x,int y){
 x = finds(x), y = finds(y);
 if(x == y) return;
 ans += (LL)sz[x]*(LL)sz[y];
 sz[x] += sz[y];
 pset[y] = x;
}

void Tarjan(int u){
 num[u] = low[u] = cnt++;
 for(int i = 0 ; i < adj[u].size() ; i++){
  int v = adj[u][i];
  if(num[v] == -1){
    par[v] = u;
    Tarjan(v);
    if(low[v] <= num[u])
     uni(u,v);
    low[u] = min(low[u], low[v]);
  }
  else if(par[u] != v)
   low[u] = min(low[u],num[v]);
 }
}

inline void Solve(){
 Reset();
 Tarjan(1);
 ans = 0;
 for(int i = 1 ; i <= n ; i++)
  for(int j = 0 ; j < adj[i].size() ; j++){
   int k = adj[i][j];
   uni(i,k);
  }
 LL all = (LL)n*(LL)(n-1)/2LL;
 printf("%.5lf\n",(double)ans/(double)all);
}

inline void Read(){
 scanf("%d %d",&n,&m);
 int a,b;
 while(m--){
  scanf("%d %d",&a,&b);
  adj[a].pb(b);
  adj[b].pb(a);
 }
}

int main(){
 Read();
 Solve();
 //puts("ganteng");
 return 0;
}

