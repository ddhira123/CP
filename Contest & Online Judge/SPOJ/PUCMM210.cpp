#include <cstdio>
using namespace std;
#define mod 1000000003LL

long long prefix[1000005],b,sum[1000005],tc,a;

int main(){
 for(a=1;a<=1000000;a++)
  prefix[a]=(prefix[a-1]+a*a*a)%mod;
 for(a=1;a<=1000000;a++)
  sum[a]=(sum[a-1]+prefix[a])%mod;
 scanf("%lld",&tc);
 while(tc--){
  scanf("%lld",&a);
  printf("%lld\n",sum[a]);
 }
 return 0;
}
