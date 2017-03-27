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
typedef unsigned long long ULL;
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

struct edge{
 int id;
 int next;
 int cost;
 
 edge(int x,int y,int z){
  id=x;
  next=y;
  cost=z;
 }
};


int n,m;
vector<edge> adj[1505];
int dp[1505],dp2[1505];
int dist[1505];
int ans[5005];
bool visit[1505];

inline int add(int &x,int y){
 x+=y;
 if(x>=MOD) x-=MOD;
}

int solve(int pos){
 int &ret=dp[pos];
 if(ret!=-1) return ret;
 ret=1;
 for(int i=0;i<adj[pos].size();i++){
  int nxt=adj[pos][i].next;
  int ncos=dist[pos] + adj[pos][i].cost;
  int idx=adj[pos][i].id;
  if(ncos == dist[nxt])
   add(ret,solve(nxt));
 }
 return ret;
}

void Dijkstra(int start){
 for(int i=0;i<n;i++)
  dist[i]=INF,dp[i]=-1,dp2[i]=0,visit[i]=0;
 dist[start]=0;
 priority_queue<pii> pq;
 pq.push(mp(0,start));
 while(!pq.empty()){
  pii lol=pq.top();
  pq.pop();
  lol.fi=-lol.fi;
  if(dist[lol.se]!=lol.fi) continue;
  for(int i=0;i<adj[lol.se].size();i++){
   int nxt=adj[lol.se][i].next;
   int ncos=lol.fi + adj[lol.se][i].cost;
   if(dist[nxt] > ncos)
    dist[nxt]=ncos,pq.push(mp(-ncos,nxt));
  }
 }
 int lol=solve(start); 
 pq.push(mp(0,start));
 visit[start]=0;
 //printf("NOW %d\n",start);
 dp2[start]=1;
 while(!pq.empty()){
  pii lol=pq.top();
  pq.pop();
  lol.fi=-lol.fi;
 //add(dp2[lol.se],1);
  for(int i=0;i<adj[lol.se].size();i++){
   int nxt=adj[lol.se][i].next;
   int ncos=lol.fi + adj[lol.se][i].cost;
   int idx=adj[lol.se][i].id;
   if(dist[nxt] == ncos){
    add(ans[idx],((LL)dp2[lol.se] * (LL)dp[nxt])%MOD);
    add(dp2[nxt],dp2[lol.se]);
    if(!visit[nxt])
     visit[nxt]=1,pq.push(mp(-ncos,nxt));
   }
  }
 }
 //rintf("NOW %d\n",start);
 //for(int i=0;i<n;i++)
  //printf("%d -> IN %d OUT %d\n",i,dp2[i],dp[i]);
 //printf("NOW %d\n",start+1);
 //for(int i=0;i<n;i++)
  //printf("%d -> %d\n",i+1,dist[i]); 
}

/*int modpow(){
 LL ret=1,base=2;
 int po=MOD-2;
 while(po){
  if(po&1) ret=(ret*base)%MOD;
  base=(base*base)%MOD;
  po>>=1;
 }
 return ret;
}*/

int main(){
 //LL inverse=modpow();
 n=io(),m=io();
 for(int i=0;i<m;i++){
  int a,b,c;
  a=io(); b=io(); c=io();
  a--; b--;
  adj[a].pb(edge(i,b,c));
  //adj[b].pb(edge(i,a,c));
 }
 for(int i=0;i<n;i++)
  Dijkstra(i);
 for(int i=0;i<m;i++)
  printf("%d\n",ans[i]); 
 //puts("ganteng");
 return 0;
}
