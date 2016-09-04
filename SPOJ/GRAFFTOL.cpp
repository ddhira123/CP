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

struct Fenwick{
 int sz;
 vector<LL> BIT;
 
 Fenwick(int x){
  sz = x;
  BIT.resize(sz + 2);
 }
 
 void Update(int pos,LL val){
  for(; pos <= sz ; pos += pos&-pos)
   BIT[pos] += val;
 }
 
 LL Query(int pos){
  LL ret = 0;
  for(; pos ; pos -= pos&-pos)
   ret += BIT[pos];
  return ret; 
 }
 
 LL Query(int a,int b){
  return Query(b) - Query(a-1);
 }
};

vector<Fenwick> HLD;
int n,m;
vector<int> adj[100005];
int heavy[100005],depth[100005],sz[100005],par[100005];
int chain[100005],head[100005],id[100005];
int cost[100005];

void DFS(int pos,int prev){
 heavy[pos] = -1;
 sz[pos] = 1;
 par[pos] = prev;
 for(int i = 0 ; i < adj[pos].size() ; i++){
  int nxt = adj[pos][i];
  if(nxt == prev) continue;
  
  depth[nxt] = depth[pos] + 1;
  DFS(nxt,pos);
  sz[pos] += sz[nxt];
  if(heavy[pos] == -1 || sz[heavy[pos]] < sz[nxt])
   heavy[pos] = nxt;
 }
}

void Build_HLD(){
 DFS(1,-1);
 int cnt = 0;
 for(int i = 1 ; i <= n ; i++)
  if(par[i] == -1 || heavy[par[i]] != i){
   int it = 1;
   for(int j = i ; j != -1 ; j = heavy[j]){
    chain[j] = cnt;
    head[j] = i;
    id[j] = it;
    it++;
   }
   HLD.pb(Fenwick(it));
   cnt++;
  }

}

void Update_HLD(int pos,LL val){
 int chains = chain[pos];
 int idx = id[pos];
 HLD[chains].Update(idx,val - cost[pos]);
 cost[pos] = val;
}

LL Query_HLD(int u,int v){
 LL ret = -(cost[u] + cost[v]);
 
 while(chain[u] != chain[v]){
  //printf("%d %d\n",u,v);
  if(depth[head[u]] > depth[head[v]]){
   ret += HLD[ chain[u] ].Query(id[u]);
   u = par[head[u]];
  }
  else{
   ret += HLD[ chain[v] ].Query(id[v]);
   v = par[head[v]];  
  }
 }
 
 if(id[u] > id[v]) swap(u,v);
 ret += HLD[chain[u]].Query(id[u],id[v]);
 return ret;
}

void Read(){
 scanf("%d",&n);
 for(int i = 1 ; i < n ; i++){
  int a,b;
  scanf("%d %d",&a,&b);
  adj[a].pb(b);
  adj[b].pb(a);
  //printf("%d %d\n",a,b);
 }
}

void Process(){
 Build_HLD();
 //DEBUG;
 scanf("%d",&m);
 while(m--){
  char s[4];
  int a,b;
  scanf("%s %d %d",s,&a,&b);
  //DEBUG;
  if(s[0] == 'Q')
   printf("%lld\n",Query_HLD(a,b));
  else
   Update_HLD(a,b); 
 }
}

int main(){
 Read();
 Process();
 //puts("ganteng");
 return 0;
}

