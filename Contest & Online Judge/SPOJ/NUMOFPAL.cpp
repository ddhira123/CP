#include <cstdio>
#include <cstring>
using namespace std;

int dp[1005][1005],visited[1005][1005],s;
char x[1005];

bool pali(int l,int r){
 if(l==r)
  return 1;
 if(l+1==r)
  return x[l]==x[r];
 if(visited[l][r]!=-1)
  return visited[l][r];
 if(x[l]==x[r])
  return visited[l][r]=pali(l+1,r-1);
 return visited[l][r]=0;
}

int solve(int l,int r){
 if(l==r)
  return 1;
 if(l+1==r){
  if(x[l]==x[r])
   return 3;
  return 2;
 }
 if(dp[l][r]!=-1)
  return dp[l][r];
 dp[l][r]=solve(l+1,r)+solve(l,r-1)-solve(l+1,r-1);
 if(pali(l,r))
  dp[l][r]++;
 return dp[l][r];
}

int main(){
 scanf("%s",x);
 memset(visited,-1,sizeof visited);
 memset(dp,-1,sizeof dp);
 s=strlen(x);
 printf("%d\n",solve(0,s-1));
 return 0;
}
