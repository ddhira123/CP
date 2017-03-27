#include <cstdio>
#include <algorithm>
using namespace std;

int tc,n,m,dp[55][55],a,b,rt[8]={0,-1,-1,-1,0,1,1,1},ct[8]={-1,-1,0,1,1,1,0,-1};
char arr[55][55];
bool valid(int rr,int cc,char z){
 if(rr>=0&&rr<n&&cc>=0&&cc<m)
  return arr[rr][cc]==z+1;
 return 0;
}

int solve(int rr,int cc){
 if(dp[rr][cc]!=-1)
  return dp[rr][cc];
 int res=0;
 for(int i=0;i<8;i++)
  if(valid(rr+rt[i],cc+ct[i],arr[rr][cc]))
   res=max(res,solve(rr+rt[i],cc+ct[i]));
 return dp[rr][cc]=res+1;
}

int main(){
 scanf("%d %d",&n,&m);
 while(n|m){
  getchar();
  for(a=0;a<n;a++){
   for(b=0;b<m;b++){
    dp[a][b]=-1;
    scanf("%c",&arr[a][b]);
   }
   getchar();
  }
 int ans=0;
 for(a=0;a<n;a++)
  for(b=0;b<m;b++)
   if(arr[a][b]=='A')
    ans=max(ans,solve(a,b));
 printf("Case %d: %d\n",++tc,ans);
 scanf("%d %d",&n,&m);
 }
 return 0;
}