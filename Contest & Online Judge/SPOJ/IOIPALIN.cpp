#include <algorithm>
#include <cstdio>
using namespace std;

int dp[2][5005],n,a,b;
char x[5005];

int main(){
 scanf("%d",&n);
 getchar();
 for(a=0;a<n;a++)
  scanf("%c",&x[a]);
 for(a=1;a<=n;a++)
  for(b=1;b<=n;b++)
   if(x[a-1]==x[n-b])
    dp[a%2][b]=1+dp[(a-1)%2][b-1];
   else
    dp[a%2][b]=max(dp[(a-1)%2][b],dp[a%2][b-1]);
 printf("%d\n",n-dp[n%2][n]);
 return 0;
}
