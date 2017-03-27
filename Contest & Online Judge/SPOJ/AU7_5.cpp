#include <cstdio>
using namespace std;
#define mod 5000011
int dp[100005][2],n,k,tc;

int solve(int pos,int op){
 if(pos>=n)
  return 1;
 if(dp[pos][op]!=-1)
  return dp[pos][op];
 if(op==0)
  return dp[pos][op]=(solve(pos+1,0)+solve(pos+1,1))%mod;
 return dp[pos][op]=solve(pos+k,0)%mod;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d",&n,&k);
  for(int a=0;a<=n;a++)
   dp[a][0]=dp[a][1]=-1;
  printf("%d\n",(solve(1,0)+solve(1,1))%mod);
 }
 return 0;
}
