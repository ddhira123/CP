#include <cstdio>
using namespace std;
#define MOD 1000000007LL
long long tc,n,ans,mul;

int main(){
 scanf("%lld",&tc);
 while(tc--){
  scanf("%lld",&n);
  n--;
  ans=1;
  mul=2;
  while(n){
   if(n&1) ans=(ans*mul)%MOD;
   mul=(mul*mul)%MOD;
   n>>=1;
  }
  printf("%lld\n",ans);
 }
 return 0;
}
