#include <cstdio>
#include <algorithm>
using namespace std;

int ki[1005][1005],ka[1005][1005],pos[1005],dp[1005][1005],n,tc,a,b;

int solve(int l,int r){
 if(dp[l][r]!=-1)
  return dp[l][r];
 int res=1000000001;
 if(l>=1)
  res=min(res,(r-l)*(pos[l]-ki[l][r-1])+solve(l-1,r));
 if(r<=n)
  res=min(res,(r-l)*(pos[r]-ka[r][l+1])+solve(l,r+1));
 return dp[l][r]=res;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(a=0;a<=n+1;a++)
   for(b=0;b<=n+1;b++){
    ki[a][b]=ka[a][b]=0;
    dp[a][b]=-1;
   }
  for(a=1;a<=n;a++){
   scanf("%d",&b);
   pos[b]=a;
  }
  for(a=1;a<=n;a++){
   int tot=0;
   for(b=a;b<=n;b++){
    tot+=(pos[a]>pos[b]);
    ki[a][b]=tot;
   }
  }
  for(a=n;a>=1;a--){
   int tot=0;
   for(b=a;b>=1;b--){
    tot+=(pos[a]>pos[b]);
    ka[a][b]=tot;
   }
  }
  dp[0][n+1]=0;
   int ans=1000000001;
   for(a=1;a<=n;a++){
    ans=min(ans,pos[a]+solve(a-1,a+1));
    //printf("%d %d\n",a,pos[a]+solve(a-1,a+1));
   }
   printf("%d\n",ans);
 }
 return 0;
}
