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

const int MAXN = 50005;

struct Fenwick{
 vector<int> BIT;
 int sz;
 
 Fenwick(int x){
  sz = x;
  BIT.resize(x+1);
 }
 
 void Update(int x,int val){
  for(; x <= sz ; x += x & -x)
   BIT[x] += val;
 }
 
 void Update(int x,int y,int val){
  Update(x,val);
  Update(y+1,-val);
 }
 
 int Query(int x){
  int ret = 0;
  for(; x ; x -= x & -x)
   ret += BIT[x];
  return ret; 
 }
};

vector<Fenwick> HLD;
vector<int> adj[MAXN];
int chain[MAXN], sub[MAXN], heavy[MAXN];
int head[MAXN], pos[MAXN], par[MAXN];
int depth[MAXN];
int tc,n,m;

void Reset(){
 HLD.clear();
 for(int i = 0 ; i < n ; i++){
  adj[i].clear();
  heavy[i] = -1;
  sub[i] = 1;
 } 
}

void DFS(int pos,int prev){
 for(int i = 0 ; i < adj[pos].size() ; i++){
  int nxt = adj[pos][i];
  if(nxt == prev) continue;
  
  par[nxt] = pos;
  depth[nxt] = depth[pos] + 1;
  DFS(nxt,pos);
  sub[pos] += sub[nxt];
  if(heavy[pos] == -1 || sub[heavy[pos]] < sub[nxt])
   heavy[pos] = nxt;
 }
}

void Build_HLD(){
 par[0] = -1;
 DFS(0,-1);
 int cnt = 0;
 for(int i = 0 ; i < n ; i++)
  if(par[i] == -1 || heavy[par[i]] != i){
   int it = 1;
   for(int j = i ; j != -1 ; j = heavy[j]){
    head[j] = i;
    chain[j] = cnt;
    pos[j] = it++;
   }
   HLD.pb(Fenwick(it));
   cnt++;
  }
}

void Update_HLD(int u,int v,int val){
 while(chain[u] != chain[v]){
  if(depth[head[u]] < depth[head[v]]) swap(u,v);
  HLD[chain[u]].Update(1,pos[u],val);
  u = par[head[u]];
 }
 if(pos[u] > pos[v]) swap(u,v);
 HLD[chain[u]].Update(pos[u],pos[v],val);
}

void Read(){
 //scanf("%d",&n);
 n = io();
 Reset();
 int a,b;
 for(int i = 1 ; i < n ; i++){
  //scanf("%d %d",&a,&b);
  a = io(); b = io();
  adj[a].pb(b);
  adj[b].pb(a);
 }
}

void Process(){
 //scanf("%d",&m);
 m = io();
 int a,b,k;
 while(m--){
  //scanf("%d %d %d",&a,&b,&k);
  a = io() ; b = io() ; k = io();
  if(k == -1)
   printf("%d %d\n",HLD[chain[a]].Query(pos[a]),HLD[chain[b]].Query(pos[b]));
  else
   Update_HLD(a,b,k); 
 }
}

int main(){
 //scanf("%d",&tc);
 tc = io();
 while(tc--){
  Read();
  Build_HLD();
  Process();
 }
 //puts("ganteng");
 return 0;
}

