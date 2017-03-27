#include <cstdio>
#include <algorithm>
using namespace std;
#define INF 1000000000
int dp[16][(1<<16)+5],n,arr[20],C[20],tc,tgt;

int countbit(int x){
 int res=0;
 while(x){
  res++;
  x&=(x-1);
 }
 return res;
}

int PlayDP(int last,int mask){
 if(mask==tgt) return 0;
 if(dp[last][mask]!=-1) return dp[last][mask];
 int ret=INF,jum=countbit(mask);
 for(int i=0;i<n;i++)
  if((mask&(1<<i))==0)
   ret=min(ret,C[jum]*abs(arr[i]-arr[last])+PlayDP(i,mask|(1<<i)));
 return dp[last][mask]=ret;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  tgt=(1<<n)-1;
  for(int i=0;i<n;i++)
   for(int j=0;j<=tgt;j++)
    dp[i][j]=-1;
  for(int i=0;i<n;i++)
   scanf("%d",&arr[i]);
  for(int i=0;i<n;i++)
   scanf("%d",&C[i]);
  int ans=INF;
  for(int i=0;i<n;i++)
   ans=min(ans,PlayDP(i,(1<<i)));
  printf("%d\n",ans);
 }
 return 0;
}
