#include <cstdio>
#include <algorithm>
using namespace std;
#define INF 1000000000

int dp[105][105][105],n,k,tc,price[105];

int solve(int pos,int packet_left,int left){
 if(packet_left<0||left<0)
  return INF;
 if(pos>k){
  if(left==0)
   return 0;
  return INF;
 }
 if(dp[pos][packet_left][left]!=-1)
  return dp[pos][packet_left][left];
 int ans=solve(pos+1,packet_left,left);
 if(price[pos]!=-1)
  ans=min(ans,price[pos]+solve(pos,packet_left-1,left-pos));
 return dp[pos][packet_left][left]=ans;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d",&n,&k);
  for(int a=0;a<=k;a++)
    for(int c=0;c<=n;c++)
     for(int b=0;b<=k;b++)
       dp[a][c][b]=-1;
  for(int a=1;a<=k;a++)
   scanf("%d",&price[a]);
  int res=solve(1,n,k);
  if(res>=INF)
   printf("-1\n");
  else
   printf("%d\n",res);
 }
 return 0;
}