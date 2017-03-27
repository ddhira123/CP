#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char x[2005],y[2005];
int dp[2005][2005],n,m,s;

int solve(int l,int r){
 if(l==0)
  return r*s;
 if(r==0)
  return l*s;
 if(dp[l][r]!=-1)
  return dp[l][r];
 int ans=s+min(solve(l,r-1),solve(l-1,r));
 ans=min(ans,abs(x[l-1]-y[r-1])+solve(l-1,r-1));
 return dp[l][r]=ans;
}

int main(){
 scanf("%s",x);
 scanf("%s",y);
 scanf("%d",&s);
 n=strlen(x);
 m=strlen(y);
 for(int a=0;a<=n;a++)
  for(int b=0;b<=m;b++)
   dp[a][b]=-1;
 printf("%d\n",solve(n,m));
 return 0;
}