#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
using namespace std;
#define INF 1000000000
int dist[20][20];
int dp[(1<<16)+5];
int n,m;
int x,y,z;

inline void Reset(){
 for(int i=0;i<n;i++)
  for(int j=0;j<n;j++)
   dist[i][j]=INF;
 for(int i=0;i<n;i++)
  dist[i][i]=0;
}

inline void Warshall(){
 for(int i=0;i<n;i++)
  for(int j=0;j<n;j++)
   for(int k=0;k<n;k++)
    dist[j][k]=min(dist[j][i]+dist[i][k],dist[j][k]);
}

inline int Solve(int bit){
 if(dp[bit]!=-1) return dp[bit];
 dp[bit]=INF;
 int i;
 for(i=0;i<n;i++)
  if(bit&(1<<i))
   break;
 for(int j=i+1;j<n;j++)
  if((bit&(1<<j)) )
   dp[bit]=min(dp[bit],dist[i][j]+Solve(bit^( (1<<i) | (1<<j) ) ) );
 return dp[bit];
}

int main(){
 scanf("%d",&n);
 while(n){
  scanf("%d",&m);
  Reset();
  int bit=0,res=0;
  while(m--){
   scanf("%d %d %d",&x,&y,&z);
   x--; y--;
   res+=z;
   dist[x][y]=min(dist[x][y],z);
   dist[y][x]=dist[x][y];
   bit^=(1<<x);
   bit^=(1<<y);
  }
  memset(dp,-1,sizeof dp);
  dp[0]=0;
  Warshall();
  //printf("%d %d\n",res,Solve(bit));
  printf("%d\n",res+Solve(bit));
  scanf("%d",&n);
 }
 return 0;
}
