#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char x[2005],y[2005];
int tc,n,m,dp[2005][2005],a,b;

int solve(int l,int r){
 if(dp[l][r]!=-1)
  return dp[l][r];
 if(l==0)
  return dp[l][r]=r;
 if(r==0)
  return dp[l][r]=l;
 if(x[l-1]==y[r-1])
  return dp[l][r]=solve(l-1,r-1);
 return dp[l][r]=1+min(solve(l-1,r-1),min(solve(l-1,r),solve(l,r-1)));
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%s",x);
  n=strlen(x);
  scanf("%s",y);
  m=strlen(y);
  for(a=0;a<=n;a++)
   for(b=0;b<=m;b++)
    dp[a][b]=-1;
  printf("%d\n",solve(n,m));
 }
 return 0;
}