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
vector<int> adj[40];
int Parent[40];
int sz,source,sink,f;
string tmp;
int n,m,tc;

inline int ID(string xx){
 int ret;
 if(xx=="XS") ret=1;
 else if(xx=="S") ret=2;
 else if(xx=="M") ret=3;
 else if(xx=="L") ret=4;
 else if(xx=="XL") ret=5;
 else              ret=6;
 return ret;
}

inline void Add_Edge(int x,int y,int z){
 adj[x].pb(sz);
 Edgelist.pb(Edge(x,y,z));
 sz++;
 adj[y].pb(sz);
 Edgelist.pb(Edge(y,x,0));
 sz++;
}

inline void Reset_Graph(){
 sz=0;
 Edgelist.clear();
 for(int i=source;i<=sink;i++)
  adj[i].clear();
}

inline void BFS(){
 for(int i=source;i<=sink;i++) Parent[i]=-1;
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

void Augment(int pos,int Min){
 if(Min==0) return;
 else if(pos==source)
  f=Min;
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
    mf+=f;
    Edgelist[idx].flow-=f;
    Edgelist[idx^1].flow+=f;
   }
  }
 }
 return mf;
}

int main(){
 SYNC;
 cin>>tc;
 while(tc--){
  cin>>n>>m;
  n/=6;
  sink=m+7;
  Reset_Graph();
  for(int i=1;i<=6;i++)
   Add_Edge(m+i,sink,n);
  for(int i=1;i<=m;i++){
   Add_Edge(source,i,1);
   for(int j=0;j<2;j++){
    cin>>tmp;
    Add_Edge(i,m+ID(tmp),1);
   }
  }
  if(m==Max_Flow())
   cout<<"YES\n";
  else
   cout<<"NO\n";  
 }
 //puts("ganteng");
 return 0;
}

