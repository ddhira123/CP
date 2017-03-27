#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back

vector<pii> tmp,ans;
vector<int> adj[705];
int num[705],low[705],cnt,par[705],tc,n,m;

bool cmp(pii i,pii j){
 if(i.fi==j.fi)
  return i.se<j.se;
 return i.fi<j.se;
}

void PlayTarjan(int v){
 num[v]=low[v]=cnt++;
 for(int i=0;i<adj[v].size();i++){
  int u=adj[v][i];
  if(num[u]==-1){
   par[u]=v;
   PlayTarjan(u);
   if(low[u]>num[v])
    tmp.pb(mp(min(u,v),max(u,v)));
   low[v]=min(low[v],low[u]);
  }
 else if(u!=par[v])
   low[v]=min(low[v],num[u]);
 }
}

int main(){
 scanf("%d",&tc);
 for(int t=1;t<=tc;t++){
  tmp.clear(); ans.clear(); cnt=0;
  scanf("%d %d",&n,&m);
  for(int i=1;i<=n;i++){
     adj[i].clear();
     num[i]=low[i]=par[i]=-1;
  }
  while(m--){
   int a,b;
   scanf("%d %d",&a,&b);
   adj[a].pb(b);
   adj[b].pb(a);
  }
  for(int i=1;i<=n;i++)
   if(num[i]==-1)
    PlayTarjan(i);
  sort(tmp.begin(),tmp.end());
  printf("Caso #%d\n",t);
  if(tmp.empty()) puts("Sin bloqueos");
  else{
   ans.pb(tmp[0]);
   for(int i=1;i<tmp.size();i++)
    if(tmp[i].fi==tmp[i-1].fi && tmp[i].se==tmp[i-1].se) continue;
    else ans.pb(tmp[i]);
   printf("%d\n",ans.size());
   for(int i=0;i<ans.size();i++)
    printf("%d %d\n",ans[i].fi,ans[i].se);
  }
 }
 return 0;
}
