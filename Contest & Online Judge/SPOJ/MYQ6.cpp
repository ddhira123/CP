#include <cstdio>
using namespace std;

int dist[1000005],n,w[1000005],tc,idx;
long long cost1[1000005],cost2[1000005],weight,mins;

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
   scanf("%d",&w[i]);
  for(int i=1;i<n;i++)
   scanf("%d",&dist[i]);
  weight=0;
  cost2[n+1]=0;
  for(int i=1;i<=n;i++){
   cost1[i]=cost1[i-1]+weight*(long long)dist[i-1];
   weight+=(long long)w[i];
  }
  weight=0;
  for(int i=n;i>=1;i--){
   cost2[i]=cost2[i+1]+weight*(long long)dist[i]*2LL;
   weight+=(long long)w[i];
  }
  mins=1000000000000000000LL;
  for(int i=1;i<=n;i++){
   long long ret=cost1[i]+cost2[i]+(w[i] ? 10LL : 0LL);
   if(ret<mins)
    mins=ret,idx=i;
  }
  printf("%lld %d\n",mins,idx);
 }
 return 0;
}
