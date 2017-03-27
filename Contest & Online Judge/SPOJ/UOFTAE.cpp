#include <cstdio>
#include <algorithm>
using namespace std;
#define MOD 1000000007
int tc,n,dp[205][205],A[205],B[205],m;

int solve(int pos,int left){
 if(dp[pos][left]!=-1) return dp[pos][left];
 dp[pos][left]=0;
 for(int i=A[pos];i<=min(left,B[pos]);i++)
  dp[pos][left]=(dp[pos][left]+solve(pos+1,left-i))%MOD;
 return dp[pos][left];
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d",&n,&m);
  for(int i=0;i<n;i++){
   scanf("%d %d",&A[i],&B[i]);
   for(int j=0;j<=m;j++)
    dp[i][j]=-1;
  }
  dp[n][0]=1;
  for(int i=1;i<=m;i++)
   dp[n][i]=0;
  printf("%d\n",solve(0,m));
 }
 return 0;
}