#include <cstdio>
#include <algorithm>
using namespace std;

long long dp[2][2][35][35],arr[35];
int tc,n;

long long solve(int ty,int op,int l,int r){
 if(l>r)
  return 0;
 if(dp[ty][op][l][r]!=-1)
  return dp[ty][op][l][r];
 if(!op)
  return dp[ty][op][l][r]=max(solve(ty,1,l+1,r)+arr[l],solve(ty,1,l,r-1)+arr[r]);
 if(!ty)
  return dp[ty][op][l][r]=max(solve(ty,0,l+1,r),solve(ty,0,l,r-1));
 return dp[ty][op][l][r]=min(solve(ty,0,l+1,r),solve(ty,0,l,r-1));
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(int a=0;a<n;a++)
   scanf("%lld",&arr[a]);
  for(int a=0;a<n;a++)
   for(int b=0;b<n;b++)
    dp[0][0][a][b]=dp[0][1][a][b]=dp[1][0][a][b]=dp[1][1][a][b]=-1;
  printf("%lld %lld\n",solve(0,0,0,n-1),solve(1,0,0,n-1));
 }
 return 0;
}