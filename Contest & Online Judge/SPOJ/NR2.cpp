#include <cstdio>
using namespace std;

long long ans,counter[70],cnt,x,n,po;

int main(){
 scanf("%lld",&n);
 for(int i=0;i<n;i++){
  scanf("%lld",&x);
  cnt=0;
  while(x>0){
   counter[cnt]+=(x%2LL);
   cnt++;
   x/=2LL;
  }
 }
 po=1;
 for(int i=0;i<64;i++){
  if(counter[i]>0 && (n-counter[i])>0)ans+=po; //printf("%d\n",i);}
  po*=2LL;
 }
 printf("%lld\n",ans);
 return 0;
}