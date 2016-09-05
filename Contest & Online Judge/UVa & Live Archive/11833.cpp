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

int dist[255];
int n,m,s,d,a,b,p;
vector<pii> adj[255];
priority_queue<pii> pq;

inline int Dijkstra(){
 dist[s]=0;
 while(!pq.empty()) pq.pop();
 pq.push(mp(0,s));
 while(!pq.empty()){
  int dis=-pq.top().fi,pos=pq.top().se;
  pq.pop();
  if(pos==d-1) return dis;
  else if(dis==dist[pos])
   for(int i=0;i<adj[pos].size();i++){
    int nxt=adj[pos][i].fi,cost=dis+adj[pos][i].se;
    if(dist[nxt]>cost)
     dist[nxt]=cost,pq.push(mp(-cost,nxt));
   }
 }
}

int main(){
 n=io(),m=io(),d=io(),s=io();
 while(n|m|d|s){
  for(int i=0;i<n;i++)
   adj[i].clear(),dist[i]=INF;
  while(m--){
   a=io(),b=io(),p=io();
   for(int i=0;i<2;i++){
    if(a>=d-1 || (a<d-1 && a+1==b))
     adj[a].pb(mp(b,p));
    swap(a,b);
   }
  }
  printf("%d\n",Dijkstra()); 
  n=io(),m=io(),d=io(),s=io();
 }
 //puts("ganteng");
 return 0;
}

