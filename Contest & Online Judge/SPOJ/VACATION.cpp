#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int,int> pii;
#define pq priority_queue
#define fi first
#define se second
#define mp make_pair
#define INF 50000000000LL
typedef long long LL;

#define g getchar_unlocked
inline LL io(){
register char c;
while(1){
c=g();
if((c^32) && (c^10)) break;
}
register LL res=c-'0';
while(1){
c=g();
if(!(c^32) || !(c^10))
return res;
res=(res<<3)+(res<<1)+(c-'0');
 }
}

pq< pair<LL,pii> > dijk;
LL dist[205][2],ans;
vector<pair<int,LL> > adj[205];
int n,m,k,q,res;
pii query[10005];

void dijkstra(int source){
 for(int i=1;i<=n;i++)
  dist[i][0]=dist[i][1]=INF;
 dist[source][source<=k]=0;
 dijk.push(mp(0,mp(source,source<=k)));
 while(!dijk.empty()){
  pii now=dijk.top().se;
  LL hm=-dijk.top().fi;
  dijk.pop();
  if(hm==dist[now.fi][now.se])
   for(int i=0;i<adj[now.fi].size();i++){
    LL newdist=hm+adj[now.fi][i].se;
    int next=adj[now.fi][i].fi;
    if(newdist<dist[next][now.se|(next<=k)]){
     dist[next][now.se|(next<=k)]=newdist;
     dijk.push( mp( -newdist, mp(next,now.se|(next<=k) ) ) );
    }
   }
 }
}

int main(){
 n=io();m=io();k=io();q=io();
 while(m--){
  int a,b;
  LL c;
  a=io();b=io();c=io();
  adj[a].push_back(mp(b,c));
 }
 for(int i=1;i<=q;i++)
  query[i].fi=io(),query[i].se=io();
  sort(query,query+q+1);
  for(int i=1;i<=q;i++){
   if(query[i-1].fi!=query[i].fi)
    dijkstra(query[i].fi);
   if(dist[query[i].se][1]!=INF){
    res++;
    ans+=dist[query[i].se][1];
   }
  }
 printf("%d\n%lld\n",res,ans);
 return 0;
}
