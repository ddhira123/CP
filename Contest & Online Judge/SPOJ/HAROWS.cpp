#include <algorithm>
#include <cstdio>
using namespace std;
#define INF 1000000000
int dp[(1<<8)+5],n,tc,maks[10];
char x[10];

int countbit(int z){
 int ret=0;
 while(z)
  ret++,z&=(z-1);
 return ret;
}

int PlayDP(int pos,int mask){
 if(pos==n)
  return 0;
 if(dp[mask]!=-1) return dp[mask];
 int res=INF,cnt=countbit(mask);
 for(int i=0;i<n;i++)
  if(mask&(1<<i))
   cnt--;
  else if(maks[i]<=pos)
   res=min(res,abs(pos-(i+cnt))+PlayDP(pos+1,mask|(1<<i)));
 return dp[mask]=res;
}

int main(){
 scanf("%d",&tc);
 for(int t=1;t<=tc;t++){
  scanf("%d",&n);
  for(int i=0;i<(1<<n);i++) dp[i]=-1;
  for(int i=0;i<n;i++){
   scanf("%s",x);
   maks[i]=-1;
   for(int j=n-1;j>=0;j--)
    if(x[j]=='1'){
     maks[i]=j;
     break;
    }
   //printf("%d -> %d\n",i,maks[i]);
  }
  printf("Case #%d: %d\n",t,PlayDP(0,0));
 }
 return 0;
}