#include <cstdio>
#include <cstring>
using namespace std;

long long dp[6][100005];
int po[5]={8,7,6,3,2},n,tc;

long long solve(int hm,int left){
 if(left==0)
  return 1;
 if(left<0||hm==5)
  return 0;
 if(dp[hm][left]!=-1)
  return dp[hm][left];
 return dp[hm][left]=solve(hm,left-po[hm])+solve(hm+1,left);
}

int main(){
 scanf("%d",&tc);
 memset(dp,-1,sizeof dp);
 while(tc--){
  scanf("%d",&n);
  printf("%lld\n",solve(0,n));
 }
 return 0;
}