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
vector<int> adj[10005];
int dist[10005];
bool InQ[10005];
int n,ctr;
string arr[10];
int par[10005];

inline int ID(int x,int y){
 return x*n+y+1;
}

inline int In(int x){
 return x<<1;
}

inline int Out(int x){
 return (x<<1)|1;
}

inline void Reset_Graph(){
 Elist.clear();
 ctr=0;
 for(int i=Out(ID(4,n-1));i>=0;i--)
  adj[i].clear();
}

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
 for(int i=Out(ID(4,n-1));i>=0;i--)
  dist[i]=INF,InQ[i]=0;
 InQ[0]=1;
 dist[0]=0;
 q.push(0);
 while(!q.empty()){
  int pos=q.front(); 
  q.pop();
  InQ[pos]=0;
  for(int i=0;i<adj[pos].size();i++){
   int idx=adj[pos][i];
   int nxt=Elist[idx].to;
   int co=Elist[idx].cost;
   if(Elist[idx].flow > 0 && dist[pos] + co < dist[nxt]){
    dist[nxt]=dist[pos]+co;
    par[nxt]=idx;
    if(!InQ[nxt])
     InQ[nxt]=1,q.push(nxt);
   }
  }
 } 
}

inline int MCMF(){
 int ans=0;
 while(1){
  SPFA();
  if(dist[1]==INF) break;
  int cur=1,Min=INF;
  while(cur!=0){
   int idx=par[cur];
   Min=min(Min,Elist[idx].flow);
   cur=Elist[idx].from;
  }
  ans+=Min*dist[1];
  cur=1;
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
 SYNC;
 cin>>n;
 while(n){
  Reset_Graph();
  for(int i=0;i<5;i++){
   cin>>arr[i];
   if(arr[i][0]=='@'){
    Add_Edge(0,In(ID(i,0)),1,0);
    arr[i][0]='0';
   }
   Add_Edge(Out(ID(i,n-1)),1,1,0);
   for(int j=0;j<n;j++){
    Add_Edge(In(ID(i,j)),Out(ID(i,j)),1,arr[i][j]-'0'); 
    if(i>0){
     Add_Edge(Out(ID(i,j)),In(ID(i-1,j)),1,0);
     Add_Edge(Out(ID(i-1,j)),In(ID(i,j)),1,0);
    }
    if(j>0){
     Add_Edge(Out(ID(i,j)),In(ID(i,j-1)),1,0);
     Add_Edge(Out(ID(i,j-1)),In(ID(i,j)),1,0);
    }
   }
  }
  cout<<MCMF()<<"\n";
  cin>>n;
 }
 //puts("ganteng");
 return 0;
}

