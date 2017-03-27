#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define INF 1000000000
int dp[10005][2];
int m,x,tipe[10005],nil[10005],tc;

int solve(int pos,int val){
 int chld=pos<<1;
 if(chld>m){
  if(val==nil[pos]) return 0;
  return INF;
 }
 if(dp[pos][val]!=-1) return dp[pos][val];
 int ret=INF;
 if(tipe[pos]==1){
  if(val==1){
   ret=min(ret,solve(chld,1)+solve(chld+1,1));
   if(nil[pos]){
    ret=min(ret,1+solve(chld,1)+solve(chld+1,0));
    ret=min(ret,1+solve(chld,0)+solve(chld+1,1));
   }
  }
  else{
    ret=min(ret,solve(chld,0)+solve(chld+1,0));
    ret=min(ret,solve(chld,0)+solve(chld+1,1));
    ret=min(ret,solve(chld,1)+solve(chld+1,0));
  }
 }
 else{
  if(val==1){
    ret=min(ret,solve(chld,0)+solve(chld+1,1));
    ret=min(ret,solve(chld,1)+solve(chld+1,1));
    ret=min(ret,solve(chld,1)+solve(chld+1,0));
  }
  else{
   ret=min(ret,solve(chld,0)+solve(chld+1,0));
   if(nil[pos]){
     ret=min(ret,1+solve(chld,1)+solve(chld+1,0));
     ret=min(ret,1+solve(chld,0)+solve(chld+1,1));
   }
  }
 }
 return dp[pos][val]=ret;
}

int main(){
 scanf("%d",&tc);
 for(int T=1;T<=tc;T++){
  scanf("%d %d",&m,&x);
  for(int i=1;i<=m;i++)
     dp[i][0]=dp[i][1]=-1;
  for(int i=1;i<=(m-1)/2;i++)
   scanf("%d %d",&tipe[i],&nil[i]);
  for(int i=(m+1)/2;i<=m;i++)
   scanf("%d",&nil[i]);
  int res=solve(1,x);
  printf("Case #%d: ",T);
  if(res==INF)
   puts("IMPOSSIBLE");
  else
   printf("%d\n",res);
 }
 return 0;
}
