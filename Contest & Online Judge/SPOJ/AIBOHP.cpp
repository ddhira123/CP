#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int dp[2][6105],s,a,b,tc;
char x[6105];

int main(){
 scanf("%d",&tc);
 //getchar();
 while(tc--){
 getchar();
 scanf("%s",x);
 //printf("%s\n",x);
 s=strlen(x);
 for(a=0;a<2;a++)
  for(b=0;b<=s;b++)
   dp[a][b]=0;
 for(a=1;a<=s;a++)
  for(b=1;b<=s;b++)
   if(x[a-1]==x[s-b])
    dp[a%2][b]=1+dp[(a-1)%2][b-1];
   else
    dp[a%2][b]=max(dp[(a-1)%2][b],dp[a%2][b-1]);
  printf("%d\n",s-dp[s%2][s]);
 }
 return 0;
}
