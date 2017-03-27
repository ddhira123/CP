#include <cstdio>
using namespace std;
#define MOD 1000000LL
long long dp[1005];
int a;

long long solve(int x){
 if(dp[x]!=-1)
  return dp[x];
 dp[x]=0;
 for(int i=0;i<x;i++)
  dp[x]=(dp[x]+solve(i)*solve(x-i-1))%MOD;
 return dp[x];
}

int main(){
 for(a=0;a<=1000;a++)
  dp[a]=-1;
 dp[0]=1;
 scanf("%d",&a);
 while(a){
  printf("%lld\n",solve(a));
  scanf("%d",&a);
 }
 return 0;
}