#include <cstdio>
#include <cstring>
using namespace std;

long long dp[3][105][105];
int tc,a,n,k;

long long solve(int op,int pos,int left){
 if(left<0)
  return 0;
 if(dp[op][pos][left]!=-1)
  return dp[op][pos][left];
 if(pos==0)
  return dp[op][pos][left]=(left==0);
 if(op==0)
  return dp[op][pos][left]=solve(0,pos-1,left)+solve(1,pos-1,left);
 if(op==1)
  return dp[op][pos][left]=solve(0,pos-1,left)+solve(2,pos-1,left);
 if(op==2)
  return dp[op][pos][left]=solve(0,pos-1,left-1)+solve(2,pos-1,left-1);
}

int main(){
 memset(dp,-1,sizeof dp);
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d %d",&a,&n,&k);
  printf("%d %lld\n",a,(solve(0,n,k)+solve(1,n,k))/2LL);
 }
 return 0;
}