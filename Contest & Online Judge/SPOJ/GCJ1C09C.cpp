#include <cstdio>
#include <algorithm>
using namespace std;

int tc,q,p,i,arr[105],dp[105][105];

int solve(int l,int r){
 if(l+1==r)
  return 0;
 if(dp[l][r]!=-1)
  return dp[l][r];
 dp[l][r]=1000000000;
 for(int a=l+1;a<r;a++)
  dp[l][r]=min(dp[l][r],solve(l,a)+solve(a,r)+arr[r]-arr[l]-2);
 //printf("%d %d %d\n",l,r,dp[l][r]);
 return dp[l][r];
}

int main(){
 scanf("%d",&tc);
 for(i=1;i<=tc;i++){
  scanf("%d %d",&p,&q);
  for(int a=1;a<=q;a++)
   scanf("%d",&arr[a]);
  arr[q+1]=p+1;
  for(int a=0;a<=q+1;a++)
   for(int b=a;b<=q+1;b++)
    dp[a][b]=-1;
  printf("Case #%d: %d\n",i,solve(0,q+1));
 }
 return 0;
}
