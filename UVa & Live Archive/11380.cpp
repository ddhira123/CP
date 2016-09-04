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

vector<Edge> Elist;
vector<int> adj[1805];
int dist[1805],it[1805];
string arr[35];
int ctr,r,c,p;

inline int In(int x){
 return x<<1;
}

inline int Out(int x){
 return (x<<1)|1;
}

inline int ID(int x,int y){
 return x*c+y+1;
}

inline void Reset_Graph(){
 Elist.clear();
 ctr=0;
 for(int i=Out(ID(r-1,c-1));i>=0;i--)
  adj[i].clear();
}

inline void Add_Edge(int x,int y,int z){
 adj[x].pb(ctr);
 Elist.pb(Edge(x,y,z));
 ctr++;
 adj[y].pb(ctr);
 Elist.pb(Edge(y,x,0));
 ctr++;
}

int Augment(int pos,int Min){
 if(pos==1)
  return Min;
 else if(dist[pos]==dist[1] || Min==0) return 0;
 else{
  for(;it[pos]<adj[pos].size();){
   int ret;
   int idx=adj[pos][it[pos]];
   int nxt=Elist[idx].to;
   if(Elist[idx].flow>0 && dist[nxt]==dist[pos]+1){
    ret=Augment(nxt,min(Min,Elist[idx].flow));
    if(ret==0)
     it[pos]++;
    else{
     Elist[idx].flow-=ret;
     Elist[idx^1].flow+=ret;
     return ret;
    } 
   }
   else
    it[pos]++;
  }
  return 0;
 } 
}

inline void BFS(){
 queue<int> q;
 for(int i=Out(ID(r-1,c-1));i>=0;i--)
  dist[i]=INF;
 dist[0]=0;
 q.push(0);
 while(!q.empty()){
  int pos=q.front();q.pop();
  for(int i=0;i<adj[pos].size();i++){
   int idx=adj[pos][i];
   int nxt=Elist[idx].to;
   if(dist[nxt]==INF && Elist[idx].flow > 0)
    dist[nxt]=dist[pos]+1,q.push(nxt);
  }
 } 
}

inline int MF(){
 int ans=0;
 while(1){
  BFS();
  if(dist[1]==INF) break;
  for(int i=Out(ID(r-1,c-1));i>=0;i--)
   it[i]=0;
  for(;it[0]<adj[0].size();){
   int ret;
   int idx=adj[0][it[0]];
   int nxt=Elist[idx].to;
   if(Elist[idx].flow>0 && dist[nxt]==dist[0]+1){
    ret=Augment(nxt,Elist[idx].flow);
    if(ret==0)
     it[0]++;
    else{
     Elist[idx].flow-=ret;
     Elist[idx^1].flow+=ret;
     ans+=ret;
    } 
   }
   else
    it[0]++;   
  } 
 }
 return ans;
}

int main(){
 SYNC;
 while(cin>>r){
  cin>>c>>p;
  Reset_Graph();
  for(int i=0;i<r;i++){
   cin>>arr[i];
   for(int j=0;j<c;j++){
    if(arr[i][j]!='~'){
     if(j>0 && arr[i][j-1]!='~'){ //cek kiri
      Add_Edge(Out(ID(i,j)),In(ID(i,j-1)),INF);
      Add_Edge(Out(ID(i,j-1)),In(ID(i,j)),INF);
     }
     if(i>0 && arr[i-1][j]!='~'){ //cek atas
      Add_Edge(Out(ID(i,j)),In(ID(i-1,j)),INF);
      Add_Edge(Out(ID(i-1,j)),In(ID(i,j)),INF);
     } 
    }
    if(arr[i][j]=='*'){ //orang
     Add_Edge(0,In(ID(i,j)),INF);
     Add_Edge(In(ID(i,j)),Out(ID(i,j)),1);
    }
    else if(arr[i][j]=='.') // es kecil
     Add_Edge(In(ID(i,j)),Out(ID(i,j)),1);
    else if(arr[i][j]=='@') // es besar
     Add_Edge(In(ID(i,j)),Out(ID(i,j)),INF);
    else if(arr[i][j]=='#'){ // kayu
     Add_Edge(In(ID(i,j)),Out(ID(i,j)),INF);
     Add_Edge(Out(ID(i,j)),1,p);               
    }
   }
  }
  cout<<MF()<<"\n";
 }
 //puts("ganteng");
 return 0;
}

