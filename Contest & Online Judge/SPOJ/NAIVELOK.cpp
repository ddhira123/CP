#include <cstdio>
#include <cstring>
using namespace std;
#define MOD 1000000007
int po[105],dp[105][105],len,tc;
char x[105];

int main(){
 po[0]=1;
 for(int i=1;i<=100;i++)
  po[i]=(po[i-1]<<1)%MOD;
 scanf("%d",&tc);
 while(tc--){
  scanf("%s",x);
  len=strlen(x);
  //for(int i=0;i<len;i++)
   //for(int j=0;j<len;j++)
    //dp[i][j]=0;
  int ans=po[len]-1;
  //printf("%d\n",ans);
  for(int i=0;i<len;i++)
   dp[i][i]=1;
  for(int i=1;i<len;i++)
   dp[i][i-1]=0;
  for(int j=1;j<len;j++)
   for(int i=0;j+i<len;i++){
    dp[i][i+j]=(dp[i+1][i+j]+dp[i][i+j-1])%MOD;
    if(x[i]==x[i+j]) dp[i][i+j]=(dp[i][i+j]+1)%MOD;
    else {
     dp[i][i+j]=(dp[i][i+j]-dp[i+1][i+j-1])%MOD;
     while(dp[i][i+j]<0) dp[i][i+j]+=MOD;
    }
   }
  ans-=dp[0][len-1];
  while(ans<0) ans+=MOD;
  printf("%d\n",ans);
 }
 return 0;
}
