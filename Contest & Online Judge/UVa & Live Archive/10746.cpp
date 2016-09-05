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
 double cost;
 Edge(int x,int y,int z,double co){
  from=x,to=y,flow=z,cost=co;
 }
};

vector<Edge> Elist;
vector<int> adj[45];
double dist[45];
int par[45];
int ctr,n,m;


inline void Add_Edge(int x,int y,int z,double co){
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
 for(int i=0;i<=n+m+1;i++)
  In[i]=0,dist[i]=1000000000.0;
 dist[0]=0.0;
 In[0]=1;
 q.push(0);
 while(!q.empty()){
  int pos=q.front();
  q.pop();
  for(int i=0;i<adj[pos].size();i++){
   int idx=adj[pos][i];
   int nxt=Elist[idx].to;
   int ff=Elist[idx].flow;
   double co=Elist[idx].cost;
   if(ff > 0 && dist[pos]+co+EPS<dist[nxt]){
    dist[nxt]=dist[pos]+co;
    par[nxt]=idx;
    if(!In[nxt])
     In[nxt]=1,q.push(nxt);
   }
  }
  In[pos]=0;
 } 
}

inline double MCMF(){
 double ans=0;
 //int tot=0;
 while(1){
  //DEBUG;
  SPFA();
  if(fabs(dist[n+m+1]-1000000000.0)<EPS) break;
  int cur=n+m+1;
  int Min=INF;
  while(cur!=0){
   int idx=par[cur];
   int prev=Elist[idx].from;
   int ff=Elist[idx].flow;
   Min=min(Min,ff);
   cur=prev;
  }
  cur=n+m+1;
  ans+=(double)Min*dist[n+m+1];
  //tot+=Min;
  //printf("%d\n",tot);
  while(cur!=0){
   int idx=par[cur];
   int prev=Elist[idx].from;
   Elist[idx].flow-=Min;
   Elist[idx^1].flow+=Min;
   cur=prev;
  }
 }
 return ans;
}

inline void Reset_Graph(){
 ctr=0;
 Elist.clear();
 for(int i=0;i<=n+m+1;i++)
  adj[i].clear();
}

int main(){
 scanf("%d %d",&n,&m);
 while(n|m){
  Reset_Graph();
  for(int i=1;i<=m;i++)
   Add_Edge(0,i,1,0.0);
  for(int i=1;i<=n;i++){
   Add_Edge(m+i,n+m+1,1,0.0);
   for(int j=1;j<=m;j++){
    double x;
    scanf("%lf",&x);
    Add_Edge(j,m+i,1,x);
   }
  }
  printf("%.2lf\n",(MCMF()+EPS)/(double)n);
  scanf("%d %d",&n,&m);
 }
 //puts("ganteng");
 return 0;
}

