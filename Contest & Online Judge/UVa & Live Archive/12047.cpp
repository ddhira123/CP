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
#define g getchar_unlocked
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL
#define DEBUG puts("DEBUG")


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
#define N 10000

int n,m,s,t,p;
int a,b,d;
int dist[2][N+5];
vector<pii> adj[2][N+5];
priority_queue<pii> pq;
int tc;

inline void Dijkstra(int id){
 if(id)
  dist[id][t]=0,pq.push(mp(0,t));
 else
  dist[id][s]=0,pq.push(mp(0,s));
 while(!pq.empty()){
  int dis=-pq.top().fi,pos=pq.top().se;
  pq.pop();
  if(dis==dist[id][pos])
   for(int i=0;i<adj[id][pos].size();i++){
    int nxt=adj[id][pos][i].fi,cost=dis+adj[id][pos][i].se;
    if(dist[id][nxt] > cost)
     dist[id][nxt]=cost,pq.push(mp(-cost,nxt));
   }
 }  
}

int main(){
 tc=io();
 while(tc--){
  n=io(),m=io(),s=io(),t=io(),p=io();
  for(int i=0;i<2;i++)
   for(int j=1;j<=n;j++)
    adj[i][j].clear(),dist[i][j]=INF;
  while(m--){
   a=io(),b=io(),d=io();
   adj[0][a].pb(mp(b,d));
   adj[1][b].pb(mp(a,d));
  }
  for(int i=0;i<2;i++)
   Dijkstra(i);
  int ans=-1; 
  for(int i=1;i<=n;i++)
   for(int j=0;j<adj[0][i].size();j++){
    int nxt=adj[0][i][j].fi,weight=adj[0][i][j].se;
    if(dist[0][i] + weight + dist[1][nxt] <=p )
     ans=max(ans,weight);
   }  
  //DEBUG; 
  printf("%d\n",ans); 
 }
 //puts("ganteng");
 return 0;
}

