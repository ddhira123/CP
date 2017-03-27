#include <cstdio>
using namespace std;

long long dp[11][2001],pref[2001],ans[11][2001];
int n,m,tc;

int main(){
 for(int i=1;i<=2000;i++)
  dp[1][i]=1,pref[i]=i,ans[1][i]=i;
 for(int i=2;i<=10;i++){
  for(int j=1;j<=2000;j++)
   dp[i][j]=pref[j/2],ans[i][j]=ans[i][j-1]+dp[i][j];
  for(int j=1;j<=2000;j++)
   pref[j]=pref[j-1]+dp[i][j];
 }
 scanf("%d",&tc);
 for(int i=1;i<=tc;i++){
  scanf("%d %d",&n,&m);
  printf("Data set %d: %d %d %lld\n",i,n,m,ans[n][m]);
 }
 return 0;
}
