#include <cstdio>
using namespace std;

long long dp[1<<20];
int n,mau[25][25],a,b,tc;

long long solve(int jum,int mask){
 if(dp[mask]!=-1)
  return dp[mask];
 dp[mask]=0;
 for(int i=0;i<n;i++)
  if(mau[jum][i]&&(mask&(1<<i)))
   dp[mask]+=solve(jum+1,mask^(1<<i));
  return dp[mask];
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(a=0;a<n;a++)
   for(b=0;b<n;b++)
    scanf("%d",&mau[a][b]);
  dp[0]=1;
  for(a=1;a<(1<<n);a++)
   dp[a]=-1;
  printf("%lld\n",solve(0,(1<<n)-1));
 }
 return 0;
}