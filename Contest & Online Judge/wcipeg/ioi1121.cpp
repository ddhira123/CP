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

LL dist[100005][2]; // 0 shortest,1 second shortest
int p[100005];
vector<pair<int,LL> > adj[100005];
int n,k,m;
bool vis[100005];

inline void Dijkstra(){
 priority_queue<pair<LL,int> > pq;
 for(int i=0;i<n;i++)
  dist[i][0]=dist[i][1]=INFLL;
 for(int i=0;i<k;i++)
  dist[p[i]][0]=dist[p[i]][1]=0,pq.push(mp(0,p[i]));
 while(!pq.empty()){
  LL dis=-pq.top().fi;
  int now=pq.top().se;
  pq.pop();
  if(dis==dist[now][1] && !vis[now]){
   vis[now]=1;
   for(int i=0;i<adj[now].size();i++){
    int nxt=adj[now][i].fi;
    LL cost=dis+adj[now][i].se;
    if(cost < dist[nxt][0]){
     dist[nxt][1]=dist[nxt][0];
     dist[nxt][0]=cost;
     pq.push(mp(-dist[nxt][1],nxt));
     vis[nxt]=0;
    }
    else if(cost < dist[nxt][1])
     vis[nxt]=0,dist[nxt][1]=cost,pq.push(mp(-cost,nxt));
   }
  } 
 } 
}

int main(){
 SYNC;
 cin>>n>>m>>k;
 while(m--){
  int a,b,d;
  cin>>a>>b>>d;
  adj[a].pb(mp(b,d));
  adj[b].pb(mp(a,d));
 }
 for(int i=0;i<k;i++)
  cin>>p[i];
 Dijkstra();
 //for(int i=0;i<n;i++)
  //cout<<i<<" "<<dist[i][0]<<" "<<dist[i][1]<<"\n; //buat ngecek doang tadi
 
 cout<<dist[0][1]<<"\n";
 
 //puts("ganteng");
 return 0;
}

