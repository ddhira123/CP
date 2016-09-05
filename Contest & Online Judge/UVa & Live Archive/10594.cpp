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

struct Edge{
 int from;
 int to;
 LL flow;
 LL cost;
 Edge(int x,int y,LL z,LL co){
  from=x,to=y,flow=z,cost=co;
 }
};

vector<Edge> Elist;
vector<int> adj[105];
LL dist[105];
int n,m,ctr;
bool In[105];
int par[105];

inline void Reset_Graph(){
 Elist.clear();
 ctr=0;
 for(int i=0;i<=n;i++)
  adj[i].clear();
}

inline void Add_Edge(int x,int y,LL co){
 adj[x].pb(ctr);
 Elist.pb(Edge(x,y,0LL,co));
 ctr++;
 adj[y].pb(ctr);
 Elist.pb(Edge(y,x,0LL,-co));
 ctr++;
}

inline void SPFA(){
 queue<int> q;
 for(int i=0;i<=n;i++)
  In[i]=0,dist[i]=INFLL;
 dist[0]=0LL;
 In[0]=1;
 q.push(0);
 while(!q.empty()){
  int pos=q.front();
  q.pop();
  for(int i=0;i<adj[pos].size();i++){
   int idx=adj[pos][i];
   int nxt=Elist[idx].to;
   LL co=Elist[idx].cost;
   if(Elist[idx].flow && dist[pos]+co < dist[nxt]){
    dist[nxt]=dist[pos]+co;
    par[nxt]=idx;
    if(!In[nxt])
     In[nxt]=1,q.push(nxt);
   }
  }
  In[pos]=0;
 } 
}

pll MCMF(){
 pll ans=mp(0LL,0LL);
 while(1){
  SPFA();
  if(dist[n]==INFLL) break;
  int cur=n;
  LL Min=INFLL;
  while(cur!=0){
   int idx=par[cur];
   Min=min(Min,Elist[idx].flow);
   cur=Elist[idx].from;
  }
  ans.fi+=Min*dist[n];
  ans.se+=Min;
  cur=n;
  while(cur!=0){
   int idx=par[cur];
   Elist[idx].flow-=Min;
   Elist[idx^1].flow+=Min;
   cur=Elist[idx].from;
  }
 }
 return ans;
}

int main(){
 while(scanf("%d %d",&n,&m)==2){
  Reset_Graph();
  while(m--){
   int x,y;
   LL z;
   scanf("%d %d %lld",&x,&y,&z);
   Add_Edge(x,y,z);
   Add_Edge(y,x,z);
  }
  LL d,k;
  scanf("%lld %lld",&d,&k);
  for(int i=0;i<ctr;i+=2)
   Elist[i].flow=k;
  Add_Edge(0,1,0LL);
  Elist[ctr-2].flow=d; 
  pll ret=MCMF();
  if(ret.se < d)
   puts("Impossible.");
  else
   printf("%lld\n",ret.fi); 
 }
 //puts("ganteng");
 return 0;
}

