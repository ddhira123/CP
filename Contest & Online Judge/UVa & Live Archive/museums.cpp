#include <cstdio>
#include <algorithm>
using namespace std;

int dist[15][15],dp[14][(1<<14)+5];
int fun[15],fee[15],ffun[(1<<14)+5],ffee[(1<<14)+5];
int d,t,n,m,tc;

inline void reset(){
 for(int i=0;i<=n;i++){
  for(int j=0;j<=n;j++)
   dist[i][j]=1000000000;
  for(int j=0;j<1<<(n+1);j++)
   dp[i][j]=1000000000; 
 }
 for(int i=0;i<=n;i++)
  dist[i][i]=0;
 dp[0][1]=0; 
}

inline void pre(){
 for(int i=0;i<1<<(n+1);i++){
  ffun[i]=ffee[i]=0;
  for(int j=0;j<=n;j++)
   if(i&(1<<j)){
    ffee[i]=fee[j]+ffee[i^(1<<j)];
    ffun[i]=fun[j]+ffun[i^(1<<j)];
    break;
   }
 }
}

inline void warshall(){
 for(int i=0;i<=n;i++)
  for(int j=0;j<=n;j++)
   for(int k=0;k<=n;k++)
    dist[j][k]=min(dist[j][k],dist[j][i]+dist[i][k]);
}

inline void PlayDP(){
 int ans=0;
 for(int i=1;i<1<<(n+1);i++)
  if(ffee[i]<=d)
  for(int j=0;j<=n;j++)
   if(dp[j][i]<=t){
    if(dist[j][0]+dp[j][i]<=t) ans=max(ans,ffun[i]);
    for(int k=0;k<=n;k++)
     if((i&(1<<k))==0 && ffee[i|(1<<k)]<=d)
      dp[k][i|(1<<k)]=min(dp[k][i|(1<<k)],dp[j][i]+dist[j][k]+15);
   }
 if(ans==0) printf("No possible trip.\n");
 else       printf("%d\n",ans);  
}
#define g getchar_unlocked
inline int io(){
 register char c;
 while(1){
  c=g();
  if(c!=' ' && c!='\n') break;
 }
 int ret=c-'0';
 while(1){
  c=g();
  if(c==' ' || c=='\n' || c==EOF) break;
  ret=(ret<<3)+(ret<<1)+c-'0';
 }
 return ret;
}

int main(){
 tc=io();
 for(int T=1;T<=tc;T++){
  d=io(); t=io(); n=io(); m=io();
  reset();
  for(int i=1;i<=n;i++)
   fee[i]=io(),fun[i]=io();
  pre();
  while(m--){
   int a,b,k;
   a=io(); b=io(); k=io();
   dist[a][b]=min(dist[a][b],k);
   dist[b][a]=min(dist[b][a],k);
  } 
  warshall();
  printf("Case %d: ",T);
  PlayDP();
 }
}
