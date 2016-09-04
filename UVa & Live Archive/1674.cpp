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
 vector<int> BIT;
 int sz;
 
 Fenwick(int x){
  sz=x;
  BIT.resize(x+5);
 }
 
 void Update(int x,int val){
  for(; x<=sz ; x+= x&-x)
   BIT[x]+=val;
 }
 
 void Update(int x,int y,int val){
  Update(x,val);
  Update(y+1,-val);
 }
 
 int Query(int x){
  int ret=0;
  for(; x ; x-= x&-x)
   ret+=BIT[x];
  return ret; 
 }
};

vector<Fenwick> HLD;
int tc,n,q;
vector<int> adj[50005];
int id[50005],chain[50005],heavy[50005];
int head[50005],sub[50005],depth[50005];
int par[50005];

void DFS(int now,int prev){
 par[now]=prev;
 heavy[now]=-1;
 sub[now]=1;
 for(int i=0;i<adj[now].size();i++){
  int nxt=adj[now][i];
  if(nxt==prev) continue;
  depth[nxt]=depth[now]+1;
  DFS(nxt,now);
  sub[now]+=sub[nxt];
  if(heavy[now] == -1 || sub[nxt] > sub[ heavy[now] ])
   heavy[now]=nxt;
 }
}

void Build_HLD(){
 DFS(0,-1);
 HLD.clear();
 int cnt=0;
 for(int i=0;i<n;i++)
  if(par[i]==-1 || heavy[par[i]]!=-1){
   int lol=1;
   for(int j=i ; j!=-1 ; j=heavy[j]){
    id[j] = lol++;
    chain[j] = cnt;
    head[j] = i;
   }
   cnt++;
   HLD.pb(Fenwick(lol));
  }
}

void Update(int u,int v,int val){
 int idx;
 while(chain[u] != chain[v]){
 
  if(depth[ head[u] ] > depth[ head[v] ]){
   idx=chain[u];
   HLD[idx].Update(1,id[u],val);
   u=par[ head[u] ];
  }
  
  else{
   idx=chain[v];
   HLD[idx].Update(1,id[v],val);
   v=par[ head[v] ];
  }
  
 }
 
 idx=chain[u];
 HLD[idx].Update(min(id[u],id[v]),max(id[u],id[v]),val);
}

void Answer(){
 for(int i=0;i<n;i++){
  int idx=chain[i];
  printf("%d\n",HLD[idx].Query(id[i]));
 }
}

void Read(){
 scanf("%d",&n);
 for(int i=0;i<n;i++)
  adj[i].clear();
 for(int i=1;i<n;i++){
  int a,b;
  scanf("%d %d",&a,&b);
  adj[a].pb(b);
  adj[b].pb(a);
 } 
 Build_HLD();
}

void Process(){
 scanf("%d",&q);
 while(q--){
  int a,b,c;
  scanf("%d %d %d",&a,&b,&c);
  Update(a,b,c);
 }
}

int main(){
 scanf("%d",&tc);
 for(int T=1;T<=tc;T++){
  Read();
  Process();
  printf("Case #%d:\n",T);
  Answer();
 }
 //puts("ganteng");
 return 0;
}

