#include <cstdio>
#include <algorithm>
using namespace std;

int dp[205][205][205],n,arr[205];

int solve(int maks,int mini,int now){
 if(now==n+2)
  return 0;
 if(dp[maks][mini][now]!=-1)
  return dp[maks][mini][now];
 int res=1+solve(maks,mini,now+1);
 if(arr[now]>arr[mini])
  res=min(res,solve(maks,now,now+1));
 if(arr[now]<arr[maks])
  res=min(res,solve(now,mini,now+1));
 return dp[maks][mini][now]=res;
}

int main(){
 arr[1]=1000001;
 scanf("%d",&n);
 while(n!=-1){
  for(int a=2;a<n+2;a++){
   scanf("%d",&arr[a]);
   for(int b=0;b<n+2;b++)
    for(int c=0;c<n+2;c++)
     dp[b][c][a]=-1;
  }
  printf("%d\n",solve(1,0,2));
  scanf("%d",&n);
 }
 return 0;
}