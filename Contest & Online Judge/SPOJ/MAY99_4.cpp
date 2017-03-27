#include <cstdio>
#define MOD 10000007
using namespace std;

int dp[105][105],n,r,a,b;

int solve(int pos,int left){
 if(pos==0)
  return left==0;
 if(dp[pos][left]!=-1)
  return dp[pos][left];
 int ret=0;
 for(int i=1;i<=left;i++)
  ret=(ret+solve(pos-1,left-i))%MOD;
 return dp[pos][left]=ret;
}

int main(){
 scanf("%d %d",&r,&n);
 if(n>r)
  printf("-1\n");
 else{
  for(a=0;a<=n;a++)
   for(b=0;b<=r;b++)
    dp[a][b]=-1;
  printf("%d\n",solve(n,r));
 }
 return 0;
}