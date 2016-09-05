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

bool flag[5005],can[105];
int n,m,s,e,st,en;
int x,y,z;
vector<pair<pii,int> > adj[105];
int dist[105];

inline void Dijkstra(int source){
 for(int i=1;i<=n;i++)
  dist[i]=INF;
 if(can[source]){
  dist[source]=0;
  priority_queue<pii> pq;
  pq.push(mp(0,source));
  while(!pq.empty()){
   int dis=-pq.top().fi,cur=pq.top().se;
   pq.pop();
   if(dis==dist[cur])
    for(int i=0;i<adj[cur].size();i++){
     int ndis=dis+adj[cur][i].fi.fi,nxt=adj[cur][i].fi.se,id=adj[cur][i].se;
     if(can[nxt] && flag[id] && dist[nxt]>ndis)
      dist[nxt]=ndis,pq.push(mp(-ndis,nxt));
    }
  }
 } 
}

inline void BFS(int source){
 queue<int> q;
 can[source]=0;
 q.push(source);
 while(!q.empty()){
  int cur=q.front(); q.pop();
  for(int i=0;i<adj[cur].size();i++){
   int dis=adj[cur][i].fi.fi,nxt=adj[cur][i].fi.se,id=adj[cur][i].se;
   if(dist[nxt]+dis==dist[cur]){
    flag[id]=0;
    if(can[nxt])
     can[nxt]=0,q.push(nxt);
   }
  }
 }
}

int main(){
 while(scanf("%d",&n)==1){
  scanf("%d %d %d %d %d",&m,&s,&e,&st,&en);
  for(int i=1;i<=n;i++)
   adj[i].clear(),can[i]=1;
  for(int i=0;i<m;i++){
   flag[i]=1;
   scanf("%d %d %d",&x,&y,&z);
   adj[x].pb(mp(mp(z,y),i));
   adj[y].pb(mp(mp(z,x),i));
  }
  Dijkstra(s);
  BFS(e);
  Dijkstra(st);
  if(dist[en]==INF)
   puts("MISSION IMPOSSIBLE.");
  else
   printf("%d\n",dist[en]);  
 }
 //puts("ganteng");
 return 0;
}

