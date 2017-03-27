#include <cstdio>
#include <algorithm>
using namespace std;

int n,arr[10005],tc;
long long dp[10005][3];

long long solve(int pos,int op){
 if(dp[pos][op]!=-1)
  return dp[pos][op];
 if(op==1)
   return dp[pos][op]=arr[pos]+solve(pos+1,0);
  return dp[pos][op]=max(solve(pos+1,0),solve(pos+1,1));
}

int main(){
 scanf("%d",&tc);
 for(int i=1;i<=tc;i++){
  scanf("%d",&n);
  for(int a=0;a<n;a++){
   dp[a][0]=dp[a][1]=-1;
   scanf("%d",&arr[a]);
  }
  dp[n][0]=dp[n][1]=0;
  printf("Case %d: %lld\n",i,max(solve(0,0),solve(0,1)));
 }
 return 0;
}