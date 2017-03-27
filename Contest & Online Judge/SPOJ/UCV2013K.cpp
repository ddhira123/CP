#include <cstdio>
#include <algorithm>
using namespace std;

double dp[20][(1<<17)+5],dum,dist[20][20];
int a,b,n,m,tgt;

double playDP(int pos,int mask){
 if(mask==tgt)
    return dist[pos][0];
 if(dp[pos][mask] > -0.5)
    return dp[pos][mask];
 dp[pos][mask]=0.0;
 for(int i=0;i<=n;i++)
  if((mask&(1<<i))==0)
   dp[pos][mask]=max(dp[pos][mask],dist[pos][i]*playDP(i,mask|(1<<i)));
 return dp[pos][mask];
}

int main(){
 scanf("%d %d",&n,&m);
 while(n|m){
  tgt=(1<<(n+1))-1;
  for(int i=0;i<=n;i++){
   for(int j=0;j<=n;j++)
        dist[i][j]=0.0;
   for(int j=0;j<=tgt;j++)
    dp[i][j]=-1.0;
  }
  for(int i=0;i<m;i++){
   scanf("%d %d %lf",&a,&b,&dum);
   dum=1.0-dum;
   dist[a][b]=max(dist[a][b],dum);
   dist[b][a]=max(dist[b][a],dum);
  }
  for(int i=0;i<=n;i++)
    dist[i][i]=1.0;
  for(int i=0;i<=n;i++)
    for(int j=0;j<=n;j++)
     for(int k=0;k<=n;k++)
      dist[j][k]=max(dist[j][k],dist[j][i]*dist[i][k]);
  printf("%.3lf\n",playDP(0,1));
  scanf("%d %d",&n,&m);
 }
 return 0;
}
