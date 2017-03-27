#include <cstdio>
using namespace std;

long long dp[50][50],n,k,tc,a,b;
bool flag[50];

long long solve(int pos,int tu){
 //printf("%d %d %lld\n",pos,tu,dp[pos][tu]);
 if(tu<0)
  return 0;
 if(pos==0)
  return tu==0;
 if(dp[pos][tu]!=-1)
  return dp[pos][tu];
 //printf("%d %d\n",pos,tu);
 if(flag[pos])
  return dp[pos][tu]=solve(pos-1,tu-1);
 return dp[pos][tu]=solve(pos-1,tu-1)+solve(pos-1,tu+1);
}

int main(){
 scanf("%lld",&tc);
 while(tc--){
  scanf("%lld %lld",&n,&k);
  for(a=0;a<=2*n;a++){
   for(b=0;b<=2*n;b++)
    dp[a][b]=-1;
   flag[a]=0;
  }
  while(k--){
   scanf("%lld",&a);
   flag[a]=1;
  }
  printf("%lld\n",solve(2*n,0));
 }
 return 0;
}
