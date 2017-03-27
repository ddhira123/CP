#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define INF 1000000001
typedef pair<int,int> pii;

priority_queue<pii,vector<pii>,greater<pii> > pq;
vector<pii> adj[100005];
int dis[100005],n,m,start,fin,a,b,tc,c;

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d %d %d",&n,&m,&start,&fin);
  for(a=1;a<=n;a++){
   adj[a].clear();
   dis[a]=INF;
  }
  while(m--){
   scanf("%d %d %d",&a,&b,&c);
   adj[a].push_back(mp(c,b));
   adj[b].push_back(mp(c,a));
  }
  dis[start]=0;
  pq.push(mp(0,start));
  while(!pq.empty()){
   int jar=pq.top().fi,node=pq.top().se;
   pq.pop();
   if(jar==dis[node])
    for(a=0;a<adj[node].size();a++){
    int next=adj[node][a].se,newj=adj[node][a].fi;
     if(dis[next]>jar+newj){
      dis[next]=jar+newj;
      pq.push(mp(dis[next],next));
     }
    }
  }
  if(dis[fin]==INF)
   printf("NONE\n");
  else
   printf("%d\n",dis[fin]);
 }
 return 0;
}