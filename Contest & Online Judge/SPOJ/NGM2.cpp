#include <cstdio>
using namespace std;

int n,k,cnt;
long long ans,dum,arr[20];

long long gcd(long long a,long long b){
 if(b==0)
  return a;
 return gcd(b,a%b);
}

long long lcm(long long a,long long b){
 return a*(b/gcd(a,b));
}

int main(){
 scanf("%d %d",&n,&k);
 for(int a=0;a<k;a++)
  scanf("%lld",&arr[a]);
 ans=n;
 for(int a=1;a<(1<<k);a++){
  cnt=0,dum=1;
  for(int b=0;b<k&&dum<=n;b++)
   if(a&(1<<b)){
    cnt++;
    dum=lcm(dum,arr[b]);
   }
  if(cnt&1)
   ans-=n/dum;
  else
   ans+=n/dum;
 }
 printf("%lld\n",ans);
 return 0;
}