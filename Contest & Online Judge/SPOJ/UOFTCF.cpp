#include <cstdio>
#include <algorithm>
using namespace std;
#define INF 1000000000
int r,c,tc,dp[55][55][55];
char x[55][55];

int solve(int rr,int cc1,int cc2){
 if(rr==r)
  return 0;
 if(cc1<0 || cc1==c || x[rr][cc1]=='#') return -INF;
 if(cc2<0 || cc2==c || x[rr][cc2]=='#') return -INF;
 if(cc1==cc2) return -INF;
 if(dp[rr][cc1][cc2]!=-1) return dp[rr][cc1][cc2];
 int ret=-INF;
 for(int i=-1;i<=1;i++)
    for(int j=-1;j<=1;j++)
     ret=max(ret,solve(rr+1,cc1+i,cc2+j));
 ret+=(abs(cc1-cc2)==1);
 return dp[rr][cc1][cc2]=ret;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d",&r,&c);
  for(int i=0;i<r;i++){
   scanf("%s",x[i]);
   for(int j=0;j<c;j++)
     for(int k=0;k<c;k++)
      dp[i][j][k]=-1;
  }
  int ans=-INF;
  for(int i=0;i<c;i++)
    for(int j=0;j<c;j++)
     ans=max(ans,solve(0,i,j));
  if(ans<0)
    printf("Detour\n");
  else
    printf("%d\n",ans);
 }
 return 0;
}
