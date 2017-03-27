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

bool flag[10005];
bool vis[505];
vector<pair<int,pii> > adj[505],adjR[505]; // next/prev - cost - id
int dist[505];
int n,m,a,b,p,s,d;
priority_queue<pii> pq;
queue<int> q;

inline void PlayDijkstra(){
 for(int i=0;i<n;i++)
  dist[i]=INF;
 dist[s]=0;
 pq.push(mp(0,s));
 while(!pq.empty()){
  int dis=-pq.top().fi,pos=pq.top().se;
  pq.pop();
  if(dis==dist[pos]){
  //printf("%d %d\n",pos,dist[pos]);
  for(int i=0;i<adj[pos].size();i++){
   int id=adj[pos][i].se.se;
   if(flag[id]){
    int nxt=adj[pos][i].fi,cost=dis+adj[pos][i].se.fi;
    if(dist[nxt] > cost)
     dist[nxt]=cost,pq.push(mp(-cost,nxt));
   }
   }
  }
 } 
}

inline void BFSFlag(){
 for(int i=0;i<n;i++)
  vis[i]=0;
 vis[d]=1;
 q.push(d);
 while(!q.empty()){
  int pos=q.front();
  q.pop();
  for(int i=0;i<adjR[pos].size();i++){
   int prev=adjR[pos][i].fi,cost=adjR[pos][i].se.fi,id=adjR[pos][i].se.se;
   if(dist[prev]+cost==dist[pos]){
    flag[id]=0;
    if(!vis[prev])
     vis[prev]=1,q.push(prev);
   }
  }
 } 
}

int main(){
 n=io(),m=io();
 while(n|m){
  s=io(),d=io();
  for(int i=0;i<n;i++)
   adj[i].clear(),adjR[i].clear();
  for(int i=0;i<m;i++){
   a=io(),b=io(),p=io();
   adj[a].pb(mp(b,mp(p,i)));
   adjR[b].pb(mp(a,mp(p,i)));
   flag[i]=1;
  }
  PlayDijkstra();
  BFSFlag();
  PlayDijkstra();
  //puts("ANS");
  if(dist[d]==INF) puts("-1");
  else             printf("%d\n",dist[d]);
  n=io(),m=io();
 }
 //puts("ganteng");
 return 0;
}
