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

const int MAXN = 20005;

vector<pii> adj[MAXN];
int depth[MAXN];
pii par[MAXN][15];
int pset[MAXN];
pair<int,pii> arr[100005];
int n,m,s;

int finds(int x){
 return x == pset[x] ? x : pset[x] = finds(pset[x]);
}

void Reset(){
 for(int i = 1 ; i <= n ; i++){
  adj[i].clear();
  pset[i] = i;
 }
}

void DFS(int pos,int prev){
 for(int i = 0 ; i < adj[pos].size() ; i++){
  int nxt = adj[pos][i].fi, cost = adj[pos][i].se;
  if(nxt == prev) continue;
  depth[nxt] = depth[pos] + 1;
  par[nxt][0] = mp(pos,cost);
  for(int j = 1 ; (1 << j) <= depth[nxt] ; j++){
   pii lol = par[nxt][j-1];
   pii lol2 = par[lol.fi][j-1];
   par[nxt][j] = mp(lol2.fi,min(lol.se,lol2.se));
  }
  DFS(nxt,pos);
 }
}

int LCA(int u,int v){
 if(depth[u] < depth[v]) swap(u,v);
 int mins = INF,lg = 0;
 while((1 << lg) <= depth[u]) lg++;
 lg--;
 for(int i = lg ; i >= 0 ; i--)
  if(depth[u] - (1<<i) >= depth[v]){
   mins = min(mins,par[u][i].se);
   u = par[u][i].fi;
  }
 if(u == v) return mins;
 for(int i = lg ; i >= 0 ; i--)
  if(depth[u] >= (1<<i) && par[u][i].fi != par[v][i].fi){
   mins = min(mins,min(par[u][i].se,par[v][i].se));
   u = par[u][i].fi;
   v = par[v][i].fi;
  }
 mins = min(mins,min(par[u][0].se,par[v][0].se));
 return mins;
}

void Build(){
 sort(arr,arr+m);
 for(int i = m-1 ; i >= 0 ; i--){
  int cost = arr[i].fi;
  int a = arr[i].se.fi, b = arr[i].se.se;
  if(finds(a) != finds(b)){
   adj[a].pb(mp(b,cost));
   adj[b].pb(mp(a,cost));
   pset[finds(a)] = finds(b);
  }
 }
 DFS(1,-1);
}

int main(){
 while(scanf("%d %d %d",&n,&m,&s) == 3){
  Reset();
  for(int i = 0 ; i < m ; i++)
   scanf("%d %d %d",&arr[i].se.fi,&arr[i].se.se,&arr[i].fi);
  Build();
  while(s--){
   int a,b;
   scanf("%d %d",&a,&b);
   printf("%d\n",LCA(a,b));
  }
 }
 return 0;
}
