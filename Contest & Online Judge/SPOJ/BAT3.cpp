#include <cstdio>
#include <algorithm>
using namespace std;

int tc,n,arr[1005],robin,dp[1005];

int solve(int pos){
 if(dp[pos]!=-1) return dp[pos];
 int ret=0;
 for(int i=pos+1;i<=n;i++)
  if(arr[pos]>arr[i]) ret=max(ret,1+solve(i));
 if(pos==robin)
  for(int i=pos+1;i<=n;i++)
   if(arr[pos]<arr[i]) ret=max(ret,1+solve(i));
 return dp[pos]=ret;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d",&n,&robin);
  dp[n]=0;arr[n]=-2000000000;
  for(int i=0;i<n;i++)
   scanf("%d",&arr[i]),dp[i]=-1;
  int ans=0;
  for(int i=0;i<n;i++)
   ans=max(ans,solve(i));
  printf("%d\n",ans);
 }
 return 0;
}
