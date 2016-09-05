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

vector<int> par[5005],adj[5005];
int depth[5005];
int n,q;
int a,b;

void Build(int id,int prev){
 par[id].pb(prev);
 for(int i = 1 ; (1<<i) <= depth[id] ; i++){
  int tmp=par[id][i-1];
  int nxt=par[tmp][i-1];
  par[id].pb(nxt);
 }
}

int Get(int id,int lvl){
 for(int i = 0; (1<<i) <= lvl ; i++)
  if(lvl&(1<<i))
   id = par[id][i];
 return id;  
}

int LCA(int u,int v){
 if(depth[u] < depth[v]) swap(u,v);
 int lg=0;
 for(lg = 0 ; (1<<lg) <= depth[u] ; lg++);
 lg--;
 for(int i = lg ; i >= 0 ; i--)
  if(depth[u] - (1<<i) >= depth[v])
   u = par[u][i];
 if(u == v) return v;
 for(int i = lg ; i >= 0 ; i--)
  if(i < par[u].size() && par[u][i] != par[v][i])
   u = par[u][i] , v = par[v][i];
 return par[u][0];  
}

void DFS(int id,int prev){
 for(int i = 0; i < adj[id].size() ; i++){
  int nxt = adj[id][i];
  if(prev == nxt) continue;
  depth[nxt] = depth[id] + 1;
  Build(nxt,id);
  DFS(nxt,id);
 }
}

void Query(int u,int v){
 if(depth[u] < depth[v]) swap(u,v);
 int lca = LCA(u,v);
 int dist = depth[u] + depth[v] - 2*depth[lca];
 int meet = Get(u,dist/2);
 if(dist&1){
  int meet2 = par[meet][0];
  if(meet > meet2) swap(meet,meet2);
  printf("The fleas jump forever between %d and %d.\n",meet,meet2);
 }
 else
  printf("The fleas meet at %d.\n",meet);
}

int main(){
 scanf("%d",&n);
 while(n){
  for(int i = 1; i <= n ; i++)
   adj[i].clear() , par[i].clear();
  for(int i = 1 ; i < n ; i++){
   scanf("%d %d",&a,&b);
   adj[a].pb(b);
   adj[b].pb(a);
  } 
  DFS(1,0);
  scanf("%d",&q);
  while(q--){
   scanf("%d %d",&a,&b);
   Query(a,b);
  }
  scanf("%d",&n);
 }
 //puts("ganteng");
 return 0;
}

