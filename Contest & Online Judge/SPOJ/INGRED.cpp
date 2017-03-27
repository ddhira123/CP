#include <cstdio>
#include <algorithm>
using namespace std;
#define INF 1000000000
int n,m,dist[105][105],a,b,c,i,s,arr[11],dp[11][(1<<10)+1];

int solve(int last,int bit){
 if(bit==0)
  return 0;
 if(dp[last][bit]!=-1)
  return dp[last][bit];
 int ans=INF;
 for(int k=0;k<s+2;k++)
  if(bit&(1<<k))
   ans=min(ans,dist[arr[last]][arr[k]]+solve(k,bit^(1<<k)));
 return dp[last][bit]=ans;
}

int main(){
 scanf("%d %d",&n,&m);
 for(a=0;a<n;a++)
  for(b=0;b<n;b++)
   dist[a][b]=INF;
 for(i=0;i<m;i++){
  scanf("%d%d%d",&a,&b,&c);
  dist[a][b]=dist[b][a]=min(dist[b][a],c);
 }
 for(a=0;a<n;a++)
  dist[a][a]=0;
 for(a=0;a<n;a++)
  for(b=0;b<n;b++)
   for(c=0;c<n;c++)
    dist[b][c]=min(dist[b][c],dist[b][a]+dist[a][c]);
 scanf("%d",&s);
 for(a=2;a<s+2;a++)
  scanf("%d",&arr[a]);
 scanf("%d %d",&arr[0],&arr[1]);
 for(a=0;a<s+2;a++)
  for(b=0;b<(1<<(s+2));b++)
   dp[a][b]=-1;
 int ans=INF,tgt=(1<<(s+2))-1;
 for(a=0;a<(1<<(s+2));a++)
  if((a&1)&&!(a&2))
   ans=min(ans,solve(0,a-1)+solve(1,tgt-(a-1)-3));
 printf("%d\n",ans);
 return 0;
}
