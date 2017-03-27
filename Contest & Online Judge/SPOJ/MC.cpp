#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[1005][1005],n,m,a,b;
char x[1005],y[1005];

int solve(int l,int r){
 if(dp[l][r]!=-1)
  return dp[l][r];
 if(l==0)
  return dp[l][r]=30*r;
 if(r==0)
  return dp[l][r]=15*l;
 dp[l][r]=min(15+solve(l-1,r),30+solve(l,r-1));
 if(x[l-1]==y[r-1])
  dp[l][r]=min(dp[l][r],solve(l-1,r-1));
 return dp[l][r];
}

int main(){
 scanf("%s",x);
 while(x[0]!='#'){
  scanf("%s",y);
  n=strlen(x);
  m=strlen(y);
  for(a=0;a<=n;a++)
   for(b=0;b<=m;b++)
    dp[a][b]=-1;
  printf("%d\n",solve(n,m));
  scanf("%s",x);
 }
 return 0;
}