#include <cstdio>
using namespace std;

double dp[20][(1<<15)+5],arr[20][20];
int tc,n;

double solve(int pos,int mask){
 if(pos==n)
  return 1.0;
 if(dp[pos][mask] > -0.5)
  return dp[pos][mask];
 dp[pos][mask]=0;
 for(int a=0;a<n;a++)
  if(!(mask&(1<<a)))
   dp[pos][mask]+=arr[pos][a]*solve(pos+1,mask|(1<<a));
 return dp[pos][mask];
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(int a=0;a<n;a++){
   for(int b=0;b<n;b++)
    scanf("%lf",&arr[a][b]);
   for(int b=0;b<(1<<n);b++)
    dp[a][b]=-1.0;
  }
  printf("%.6lf\n",solve(0,0));
 }
 return 0;
}