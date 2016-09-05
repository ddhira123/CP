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
 Edge(int x,int y,int z){
  from=x,to=y,flow=z;
 }
};

vector<pair<pii,pii> > route;
vector<Edge> Edgelist;
vector<int> adj[350];
int n,d,m,tc;
int source,sink,f;
int sz;
int citizen[35],Parent[350];

inline int ID(int city,int day){
 return day*n+city;
}

inline void Add_Edge(int x,int y,int z){
 Edgelist.pb(Edge(x,y,z));
 adj[x].pb(sz);
 sz++;
 Edgelist.pb(Edge(y,x,0));
 adj[y].pb(sz);
 sz++;
}

inline void Reset_Graph(){
 Edgelist.clear();
 sz=0;
 for(int i=source;i<=sink;i++)
  adj[i].clear();
}

inline void Make_Graph(int lim){
 Reset_Graph();
 for(int i=1;i<=n;i++)
  Add_Edge(source,ID(i,0),citizen[i]);
 for(int i=0;i<d;i++)
  for(int j=1;j<=n;j++)
   Add_Edge(ID(j,i),ID(j,i+1),INF);
 for(int i=0;i<m;i++) 
  if(route[i].fi.fi<=lim)
   Add_Edge(route[i].se.fi,route[i].se.se,route[i].fi.se);
  else
   break;     
}

void Augment(int pos,int Min){
 if(Min==0) return;
 else if(pos==source) f=Min;
 else{
  int idx=Parent[pos];
  Augment(Edgelist[idx].from,min(Min,Edgelist[idx].flow));
  Edgelist[idx].flow-=f;
  Edgelist[idx^1].flow+=f;
 }
}

inline void BFS(){
 for(int i=source;i<=sink;i++)
  Parent[i]=-1;
 Parent[source]=-2;
 queue<int> q;
 q.push(source);
 while(!q.empty()){
  int pos=q.front(); q.pop();
  if(pos==sink) break;
  for(int i=0;i<adj[pos].size();i++){
   int idx=adj[pos][i];
   int nxt=Edgelist[idx].to;
   int ff=Edgelist[idx].flow;
   if(Parent[nxt]==-1 && ff>0)
    Parent[nxt]=idx,q.push(nxt);
  }
 } 
}

inline int Max_Flow(int lim){
 Make_Graph(lim);
 int mf=0;
 while(1){
  BFS();
  if(Parent[sink]==-1) break;
  for(int i=0;i<adj[sink].size();i++){
   int idx=adj[sink][i]^1;
   int prev=Edgelist[idx].from;
   int ff=Edgelist[idx].flow;
   if(Parent[prev]!=-1 && ff>0){
    f=0;
    Augment(prev,ff);
    Edgelist[idx].flow-=f;
    Edgelist[idx^1].flow+=f;
    mf+=f;
   }
  }
 }
 return mf;
}

int main(){
 tc=io();
 for(int t=1;t<=tc;t++){
  n=io(),d=io(),m=io();
  route.clear();
  sink=ID(n,d);
  for(int i=0;i<m;i++){
   int u,v,c,p,e;
   u=io(),v=io(),c=io(),p=io(),e=io();
   route.pb(mp(mp(p,c),mp(ID(u,e),ID(v,e+1) ) ) );
  }
  sort(route.begin(),route.end());
  int tot=0;
  for(int i=1;i<=n;i++)
   citizen[i]=io(),tot+=citizen[i];
  int lo=0,hi=100000;
  printf("Case #%d: ",t);
  if(Max_Flow(hi)<tot)
   puts("Impossible");
  else{
   while(lo<hi){
    int mid=(lo+hi)>>1;
    if(Max_Flow(mid)==tot) hi=mid;
    else                   lo=mid+1;
   }
   printf("%d\n",lo);
  }  
 }
 //puts("ganteng");
 return 0;
}

