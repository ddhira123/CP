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

vector<Edge> Edgelist;
int sz;
int n,m;
int source,sink,f;
int sum;
int k,dum;
vector<int> adj[1025];
int Parent[1025];
int need[25];

inline void Reset_Graph(){
 sz=0;
 Edgelist.clear();
 for(int i=source;i<=sink;i++)
  adj[i].clear();
}

inline void Add_Edge(int x,int y,int z){
 adj[x].pb(sz);
 Edgelist.pb(Edge(x,y,z));
 sz++;
 adj[y].pb(sz);
 Edgelist.pb(Edge(y,x,0));
 sz++;
}

inline void BFS(){
 for(int i=source;i<=sink;i++)
  Parent[i]=-1;
 Parent[source]=-2;
 queue<int> q;
 q.push(source);
 while(!q.empty()){
  int cur=q.front(); q.pop();
  if(cur==sink) break;
  for(int i=0;i<adj[cur].size();i++){
   int idx=adj[cur][i];
   int nxt=Edgelist[idx].to;
   int ff=Edgelist[idx].flow;
   if(Parent[nxt]==-1 && ff>0)
    Parent[nxt]=idx,q.push(nxt);
  }
 } 
}

inline void Augment(int pos,int Min){
 if(Min==0) return;
 else if(pos==source) f=Min;
 else{
  int idx=Parent[pos];
  Augment(Edgelist[idx].from,min(Min,Edgelist[idx].flow));
  Edgelist[idx].flow-=f;
  Edgelist[idx^1].flow+=f;
 }
}

inline int Max_Flow(){
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
 m=io(),n=io();
 while(n|m){
  sink=n+m+1;
  Reset_Graph();
  sum=0;
  for(int i=1;i<=m;i++){
   need[i]=io();
   sum+=need[i];
   Add_Edge(n+i,sink,need[i]);
  }
  for(int i=1;i<=n;i++){
   Add_Edge(0,i,1);
   k=io();
   while(k--){
    dum=io();
    Add_Edge(i,dum+n,1);
   }
  }
  int ret=Max_Flow();
  if(ret!=sum) puts("0");
  else{
   puts("1");
   for(int i=1;i<=m;i++){
    dum=0;
    for(int j=0;j<adj[n+i].size()&&dum<need[i];j++){
     int idx=adj[n+i][j];
     if(Edgelist[idx].flow){
      if(dum) printf(" ");
      dum++;
      printf("%d",Edgelist[idx].to);
     }
    }
    puts("");
   }
  }
  m=io(),n=io();
 }
 //puts("ganteng");
 return 0;
}

