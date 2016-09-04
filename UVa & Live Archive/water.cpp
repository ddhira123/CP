#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
#define INF 1000000000000000000LL

LL flow[25],cost[25];
LL need,time;
LL ans;
int n,q;

void DFS(LL F,LL C,int pos){
 if(F!=0 && F>=need/time){
  ans=min(ans,C);
  return;
  }
 if(pos==n) return;
 DFS(F,C,pos+1);
 DFS(F+flow[pos],C+cost[pos],pos+1); 
}

int main(){
 scanf("%d",&n);
 for(int i=0;i<n;i++)
  scanf("%lld %lld",&flow[i],&cost[i]);
 scanf("%d",&q);
 for(int t=1;t<=q;t++){
  ans=INF;
  scanf("%lld %lld",&need,&time);
  DFS(0,0,0);
  printf("Case %d: ",t);
  if(ans==INF)
   printf("IMPOSSIBLE\n");
  else
   printf("%lld\n",ans); 
 } 
 return 0;
}
