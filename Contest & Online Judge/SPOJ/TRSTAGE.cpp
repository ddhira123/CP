#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
#define EPS 1e-9
#define mp make_pair
#define se second
#define fi first
#define pb push_back
#define INF 1e9
vector<pair<int,double> > adj[35];
double ticket[10],dp[35][(1<<8)+5],hm;
int n,p,m,a,b,s,t;

double solve(int pos,int mask){
 if(pos==t) return 0.0;
 if(dp[pos][mask] > -0.5) return dp[pos][mask];
 double ret=INF;
 for(int i=0;i<adj[pos].size();i++)
  for(int j=0;j<n;j++)
   if((mask&(1<<j))==0)
    ret=min(ret,adj[pos][i].se/ticket[j]+solve(adj[pos][i].fi,mask|(1<<j)));
  return dp[pos][mask]=ret;
}

int main(){
 scanf("%d %d %d %d %d",&n,&m,&p,&s,&t);
 while(n|m|p|s|t){
 for(int i=1;i<=m;i++){
  adj[i].clear();
  for(int j=0;j<(1<<n);j++)
   dp[i][j]=-1.0;
 }
 for(int i=0;i<n;i++)
  scanf("%lf",&ticket[i]);
 while(p--){
  scanf("%d %d %lf",&a,&b,&hm);
  adj[a].pb(mp(b,hm));
  adj[b].pb(mp(a,hm));
 }
 double ans=solve(s,0);
 if(fabs(ans-INF)<EPS)
  puts("Impossible");
 else
  printf("%.6lf\n",ans);
 scanf("%d %d %d %d %d",&n,&m,&p,&s,&t);
 }
 return 0;
}