#include <cstdio>
using namespace std;
#define MOD 100000007
int dp[1030][1005],used[1030],arr[1005],n,m,tc;

int solve(int val,int pos){
 if(pos==n)
  return used[val];
 if(dp[val][pos]!=-1)
  return dp[val][pos];
 return dp[val][pos]=(solve(val,pos+1)+solve(val^arr[pos],pos+1))%MOD;
}

int main(){
 scanf("%d",&tc);
 for(int i=1;i<=tc;i++){
  scanf("%d %d",&n,&m);
  for(int a=0;a<=1024;a++)
   used[a]=1;
  for(int a=0;a<n;a++)
   scanf("%d",&arr[a]);
  for(int a=0;a<m;a++){
   int x;
   scanf("%d",&x);
   used[x]=0;
  }
  for(int a=0;a<=1024;a++)
   for(int b=0;b<n;b++)
    dp[a][b]=-1;
  printf("Case %d: %d\n",i,solve(0,0));
 }
 return 0;
}
