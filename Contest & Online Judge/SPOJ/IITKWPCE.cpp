#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

char x[2005];
int dp[2005],valid[2005][2005],tc,s;

int pali(int l,int r){
 if(l>=r)
  return 1;
 if(valid[l][r]!=-1)
  return valid[l][r];
 if(x[l]==x[r])
  return valid[l][r]=pali(l+1,r-1);
 return valid[l][r]=0;
}

int solve(int pos){
 if(dp[pos]!=-1)
  return dp[pos];
 dp[pos]=1000000000;
 for(int i=pos;i<s;i++)
  if(pali(pos,i))
   dp[pos]=min(dp[pos],1+solve(i+1));
 return dp[pos];
}

int main(){
 scanf("%d",&tc);
 getchar();
 while(tc--){
  gets(x);
  s=strlen(x);
  for(int a=0;a<s;a++){
   dp[a]=-1;
   for(int b=a;b<s;b++)
    valid[a][b]=-1;
  }
  dp[s]=0;
  printf("%d\n",solve(0));
 }
 return 0;
}