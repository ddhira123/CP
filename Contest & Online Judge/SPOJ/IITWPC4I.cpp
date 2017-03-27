#include <cstdio>
#include <algorithm>
using namespace std;
#define fi first
#define se second
#define mp make_pair
typedef long long LL;
typedef pair<int,int> pii;

pair<LL,pii > edge[300005];
int tc,n,m,cnt,a,b,c,par[100005];

void gen(){
 for(int i=0;i<=n;i++)
  par[i]=i;
}

int finds(int x){
 if(x==par[x])
  return x;
 return par[x]=finds(par[x]);
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d",&n,&m);
  cnt=0;gen();
  for(a=1;a<=n;a++){
   scanf("%d",&b);
   if(b)
    edge[cnt++]=mp(0,mp(0,a));
  }
  while(m--){
   scanf("%d %d %d",&a,&b,&c);
   edge[cnt++]=mp(c,mp(a,b));
  }
  sort(edge,edge+cnt);
  LL ans=0,jum=0;
  for(a=0;a<cnt&&jum<n;a++)
   if(finds(edge[a].se.fi)!=finds(edge[a].se.se)){
    jum++;
    ans+=edge[a].fi;
    par[finds(edge[a].se.fi)]=finds(edge[a].se.se);
   }
  if(jum==n)
   printf("%lld\n",ans);
  else
   printf("impossible\n");
 }
 return 0;
}