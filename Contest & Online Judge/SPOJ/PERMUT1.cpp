#include <cstdio>
#include <cstring>
using namespace std;

int dp[(1<<12)+5][105],tc,n,k,a,tmp,target=(1<<12)-1;

int solve(int mask,int left){
 if(left<0)
  return 0;
 if(dp[mask][left]!=-1)
  return dp[mask][left];
 if(mask==target)
  return dp[mask][left]=(left==0);
 int jum=0,ans=0;
 for(int i=0;i<12;i++)
  if(!(mask&(1<<i))){
   ans+=solve(mask|(1<<i),left-jum);
   jum++;
  }
 return dp[mask][left]=ans;
}

int main(){
 memset(dp,-1,sizeof dp);
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d",&n,&k);
  tmp=0;
  for(a=n;a<12;a++)
   tmp|=(1<<a);
  printf("%d\n",solve(tmp,k));
 }
 return 0;
}