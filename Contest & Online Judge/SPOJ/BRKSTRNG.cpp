#include <cstdio>
using namespace std;

int n,m,K[1005][1005],x[1005];
long long dp[1005][1005];

int main(){
 while(scanf("%d %d",&n,&m)==2){
  for(int i=1;i<=m;i++)
   scanf("%d",&x[i]);
  x[++m]=n;
  for(int gap=0;gap<=m;gap++)
   for(int l=0;l+gap<=m;l++){
    int r=l+gap;
    if(gap<2){
     dp[l][r]=0;
     K[l][r]=l;
     continue;
    }
    int left=K[l][r-1],right=K[l+1][r];
    dp[l][r]=1000000000000LL;
    for(int i=left;i<=right;i++){
     long long ret=dp[l][i]+dp[i][r]+(long long)(x[r]-x[l]);
     if(dp[l][r]>ret){
      dp[l][r]=ret;
      K[l][r]=i;
     }
    }
   }
  printf("%lld\n",dp[0][m]);
 }
 return 0;
}
