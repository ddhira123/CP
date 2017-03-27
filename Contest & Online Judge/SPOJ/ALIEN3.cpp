#include <cstdio>
#include <algorithm>
using namespace std;
#define INF 1000000000;
int dp[(1<<17)+5],tele[20],p,l,t,n,tgt,k;

int solve(int mask){
 if(dp[mask]!=-1) return dp[mask];
 int ret,place=0;
 for(int i=0;i<k;i++)
    if(mask&(1<<i)) place+=tele[i];
 if(place<=l) ret=l-place;
 else         ret=INF;
 for(int i=0;i<k;i++)
    if((mask&(1<<i))==0 && place+tele[i]>=0 && place+tele[i]<=n)
     ret=min(ret,1+solve(mask|(1<<i)));
 return dp[mask]=ret;
}

int main(){
 scanf("%d",&p);
 for(int i=1;i<=p;i++){
  scanf("%d %d",&n,&k);
  tgt=(1<<k)-1;
  for(int j=0;j<=tgt;j++)
    dp[j]=-1;
  for(int j=0;j<k;j++)
    scanf("%d",&tele[j]);
  scanf("%d %d",&l,&t);
  int res=solve(0);
  printf("Scenario #%d: ",i);
  if(res<=t) printf("%d\n",res);
  else       printf("-1\n");
 }
 return 0;
}
