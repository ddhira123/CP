#include <cstdio>
#include <algorithm>
using namespace std;

long long prefix[65],po[65],dp[65][65],tc,n;

long long solve(int pos,int left){
 if(pos<left)
  return 0;
 if(dp[pos][left]!=-1)
  return dp[pos][left];
 if(left==0)
  return dp[pos][left]=1;
 return dp[pos][left]=solve(pos-1,left)+solve(pos-1,left-1);
}

int main(){
 po[0]=1;
 for(int a=1;a<=60;a++){
  po[a]=po[a-1]*2LL;
 }
 for(int a=0;a<=60;a++)
  for(int b=0;b<=60;b++)
   dp[a][b]=-1;
 prefix[1]=prefix[2]=1;
 for(int a=3;a<=60;a++){
  prefix[a]=prefix[a-1];
  if(a%2==0)
   prefix[a]+=solve(a-1,a/2);
 }
 scanf("%lld",&tc);
 while(tc--){
  scanf("%lld",&n);
  printf("%lld\n",prefix[lower_bound(po,po+61,n)-po]);
 }
 return 0;
}