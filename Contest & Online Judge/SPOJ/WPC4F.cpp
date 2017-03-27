#include <cstdio>
#include <algorithm>
using namespace std;

int arr[25][5],dp[25][5],tc,n;

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(int a=0;a<n;a++)
   for(int b=0;b<3;b++)
    scanf("%d",&arr[a][b]);
  for(int b=0;b<3;b++)
   dp[n-1][b]=arr[n-1][b];
  for(int a=n-2;a>=0;a--)
   for(int b=0;b<3;b++){
    dp[a][b]=1000000000;
    for(int c=0;c<3;c++)
     if(b!=c)
      dp[a][b]=min(dp[a][b],dp[a+1][c]);
     dp[a][b]+=arr[a][b];
   }
  int ans=1000000000;
  for(int b=0;b<3;b++)
   ans=min(ans,dp[0][b]);
  printf("%d\n",ans);
 }
 return 0;
}