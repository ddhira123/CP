#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char x[55];
int dp[55][2],s;

int solve(int pos,int op){
 if(pos<0)
  return 0;
 if(dp[pos][op]!=-1)
  return dp[pos][op];
 if(op){
  dp[pos][op]=(x[pos]!='G');
  dp[pos][op]+=min(solve(pos-1,0),solve(pos-1,1));
  return dp[pos][op];
 }
 dp[pos][op]=(x[pos]!='R');
 dp[pos][op]+=solve(pos-1,0);
 return dp[pos][op];
}

int main(){
 while(scanf("%s",x)!=EOF){
  s=strlen(x);
  for(int a=0;a<s;a++)
   dp[a][0]=dp[a][1]=-1;
  printf("%d\n",min(solve(s-1,0),solve(s-1,1)));
 }
 return 0;
}