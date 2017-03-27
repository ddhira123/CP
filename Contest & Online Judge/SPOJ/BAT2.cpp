#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int dp[105][105][105],arr[105],n,tc;

int solve(int pos,int up,int lo){
 if(pos==n+2)
  return 0;
 if(dp[pos][up][lo]!=-1) return dp[pos][up][lo];
 int ret=solve(pos+1,up,lo);
 if(arr[up]>arr[pos])
  ret=max(ret,1+solve(pos+1,pos,lo));
 if(arr[pos]>arr[lo])
  ret=max(ret,1+solve(pos+1,up,pos));
 //printf("%d %d %d -> %d\n",pos,up,lo,ret);
 return dp[pos][up][lo]=ret;
}

int main(){
 arr[0]=2000000000;
 arr[1]=-arr[0];
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(int i=2;i<n+2;i++){
   scanf("%d",&arr[i]);
   for(int j=0;j<i;j++)
    for(int k=0;k<i;k++)
     dp[i][j][k]=-1;
  }
  printf("%d\n",solve(2,0,1));
 }
 return 0;
}