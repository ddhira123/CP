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
 int flow;
 int cost;
 Edge(int x,int y,int z,int co){
  from=x,to=y,flow=z,cost=co;
 }
};

vector<Edge> Elist;
vector<int> adj[105];
int dist[105];
int par[105];
int ctr,n,m;
int ans,tot;

inline void Add_Edge(int x,int y,int z,int co){
 adj[x].pb(ctr);
 Elist.pb(Edge(x,y,z,co));
 ctr++;
 adj[y].pb(ctr);
 Elist.pb(Edge(y,x,0,-co));
 ctr++;
}

inline void SPFA(){
 queue<int> q;
 bool In[105];
 for(int i=0;i<=n+1;i++)
  In[i]=0,dist[i]=INF;
 dist[0]=0;
 In[0]=1;
 q.push(0);
 while(!q.empty()){
  int pos=q.front();
  q.pop();
  for(int i=0;i<adj[pos].size();i++){
   int idx=adj[pos][i];
   int nxt=Elist[idx].to;
   int ff=Elist[idx].flow;
   int co=Elist[idx].cost;
   if(ff > 0 && dist[nxt] > dist[pos]+co){
    dist[nxt]=dist[pos]+co;
    par[nxt]=idx;
    if(!In[nxt])
     In[nxt]=1,q.push(nxt);
   }
  }
  In[pos]=0;
 } 
}

inline void MCMF(){
 ans=0,tot=0;
 while(1){
  SPFA();
  if(dist[n+1]==INF) break;
  int cur=n+1;
  int Min=INF;
  while(cur!=0){
   int idx=par[cur];
   int prev=Elist[idx].from;
   int ff=Elist[idx].flow;
   Min=min(Min,ff);
   cur=prev;
  }
  cur=n+1;
  ans+=Min*dist[n+1];
  tot+=Min;
  while(cur!=0){
   int idx=par[cur];
   int prev=Elist[idx].from;
   Elist[idx].flow-=Min;
   Elist[idx^1].flow+=Min;
   cur=prev;
  }
 }
}

inline void Reset_Graph(){
 ctr=0;
 Elist.clear();
 for(int i=0;i<=n+1;i++)
  adj[i].clear();
}

int main(){
 n=io();
 while(n){
  Reset_Graph();
  Add_Edge(0,1,2,0);
  Add_Edge(n,n+1,2,0);
  m=io();
  while(m--){
   int x,y,z;
   x=io(),y=io(),z=io();
   Add_Edge(x,y,1,z);
   Add_Edge(y,x,1,z);
  }  
  MCMF();
  if(tot<2)
   puts("Back to jail");
  else
   printf("%d\n",ans); 
  n=io();
 }
 //puts("ganteng");
 return 0;
}

