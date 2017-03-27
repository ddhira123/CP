#include <cstdio>
#include <cstring>
using namespace std;

long long dp[35],ans;
int cnt,s,tc,a;
char x[35];

long long solve(int n){
 if(dp[n]!=-1)
  return dp[n];
 dp[n]=0;
 for(int i=1;i<=n;i++)
  dp[n]+=solve(n-i);
 return dp[n];
}

int main(){
 for(a=1;a<=30;a++)
  dp[a]=-1;
 dp[0]=1;
 //for(a=1;a<=30;a++)
  //printf("%d -> %lld\n",a,solve(a));
 scanf("%d",&tc);
 while(tc--){
  scanf("%s",x);
  cnt=ans=1;
  s=strlen(x);
  for(a=1;a<s;a++)
   if(x[a]==x[a-1])
    cnt++;
   else{
    ans*=solve(cnt);
    cnt=1;
   }
  ans*=solve(cnt);
  printf("%lld\n",ans);
 }
 return 0;
}