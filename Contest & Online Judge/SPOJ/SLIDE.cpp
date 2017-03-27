#include <cstdio>
#include <algorithm>
using namespace std;
#define INF 2000000002

int dp[2][11][11],arr[10001][11],m,n;

int main(){
 scanf("%d %d",&n,&m);
 for(int i=0;i<n;i++)
  for(int j=0;j<m;j++)
   scanf("%d",&arr[i][j]);
 for(int i=0;i<m;i++)
  for(int j=0;j<m;j++)
   dp[0][i][j]=-INF;
 dp[0][0][m-1]=arr[0][0]+arr[0][m-1];
 for(int i=1;i<n;i++)
  for(int j=0;j<m;j++)
   for(int k=0;k<m;k++){
    dp[i&1][j][k]=-INF;
    for(int a=-1;a<=1;a++)
     for(int b=-1;b<=1;b++)
      if(j+a>=0 && j+a<m && k+b>=0 && k+b<m)
       dp[i&1][j][k]=max(dp[i&1][j][k],dp[(i+1)&1][j+a][k+b]);
    dp[i&1][j][k]+=arr[i][j];
    if(j!=k) dp[i&1][j][k]+=arr[i][k];
   }
 printf("%d\n",dp[(n-1)&1][0][m-1]);
 return 0;
}
