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

int n,m,q,a,b,p,s,d;
int price[1005];
int dist[1005][105],capacity;
vector<pii> adj[1005];
priority_queue<pair<int,pii> > pq;

inline void Dijkstra(){
 for(int i=n-1;i>=0;i--)
  for(int j=capacity;j>=0;j--)
   dist[i][j]=INF;
 dist[s][0]=0;
 while(!pq.empty()) pq.pop();
 pq.push(mp(0,mp(s,0)));
 while(!pq.empty()){
  int dis=-pq.top().fi,pos=pq.top().se.fi,fuel=pq.top().se.se;
  pq.pop();
  if(pos==d){
   printf("%d\n",dis);
   return;
  }
  else if(dis==dist[pos][fuel]){
   if(fuel<capacity && dist[pos][fuel+1]> dis+price[pos])
    dist[pos][fuel+1]=dis+price[pos],pq.push(mp(-dist[pos][fuel+1],mp(pos,fuel+1)));
   for(int i=0;i<adj[pos].size();i++){
    int nxt=adj[pos][i].fi,cost=adj[pos][i].se;
    if(fuel>=cost && dist[nxt][fuel-cost] > dis)
     dist[nxt][fuel-cost]=dis,pq.push(mp(-dis,mp(nxt,fuel-cost)));
   } 
  }
 }
 puts("impossible");   
}

int main(){
 n=io(),m=io();
 for(int i=0;i<n;i++)
  price[i]=io();
 while(m--){
  a=io(),b=io(),p=io();
  adj[a].pb(mp(b,p));
  adj[b].pb(mp(a,p));
 } 
 q=io();
 while(q--){
  capacity=io(),s=io(),d=io();
  Dijkstra();
   
 }
 //puts("ganteng");
 return 0;
}

