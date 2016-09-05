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

typedef pair<int,int> pii;
typedef long long LL;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SYNC ios_base::sync_with_stdio(false)
#define g getchar_unlocked
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL

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
#define N 105
struct DSU{
 int par[N];
 
 inline void reset(int x){
  for(int i=1;i<=x;i++)
   par[i]=i;
 }
 
 int finds(int x){
  return (x==par[x] ? x : par[x]=finds(par[x]));
 }
 
 inline bool issame(int x,int y){
  return finds(x)==finds(y);
 }
 
 inline void uni(int x,int y){
  if(!issame(x,y))
   par[finds(x)]=finds(y);
 }
};

int s,t,n,m,a,d;
double dist[N],b,tolerance,tmp;
int prev[N];
vector<pair<int,pair<double,double> > > adj[N]; //idx - dist - temperatur
vector<pair<double,pii> > Edgelist; // temperatur - idx1 - idx2 
priority_queue<pair<double,int> > pq;
DSU pset;

inline void PlayDijkstra(){
 for(int i=1;i<=n;i++)
  dist[i]=1000000000.0;
 dist[s]=0.0;
 pq.push(mp(0.0,s));
 while(!pq.empty()){
  double dis=-pq.top().fi;
  int id=pq.top().se;
  pq.pop();
  if(fabs(dist[id]-dis)<EPS)
   for(int i=0;i<adj[id].size();i++)
    if(adj[id][i].se.se < tolerance+EPS){
     int idx=adj[id][i].fi;
     double newdis=dis+adj[id][i].se.fi;
     //printf("%d %d %.1lf\n",id,idx,adj[id][i].se.se);
     if(newdis+EPS < dist[idx]){
      dist[idx]=newdis;
      prev[idx]=id;
      pq.push(mp(-newdis,idx));
     }
    }
 } 
}

void PrintPath(int source,int now){
 if(source!=now){
  PrintPath(source,prev[now]);
  printf(" ");
 }
 printf("%d",now);
}

int main(){
 while(scanf("%d %d",&n,&m)==2){
  pset.reset(n);
  for(int i=1;i<=n;i++)
   adj[i].clear();
  Edgelist.clear(); 
  scanf("%d %d",&s,&t);
  while(m--){
   scanf("%d %d %lf %lf",&a,&d,&tmp,&b);
   adj[a].pb(mp(d,mp(b,tmp)));
   adj[d].pb(mp(a,mp(b,tmp)));
   Edgelist.pb(mp(tmp,mp(a,d)));
  }
  sort(Edgelist.begin(),Edgelist.end());
  for(int i=0;i<Edgelist.size();i++){
   pset.uni(Edgelist[i].se.fi,Edgelist[i].se.se);
   if(pset.issame(s,t)){
    tolerance=Edgelist[i].fi;
    break;
   }
  }
  PlayDijkstra();
  PrintPath(s,t);
  printf("\n");
  printf("%.1lf %.1lf\n",dist[t],tolerance);
 }
 //puts("ganteng");
 return 0;
}

