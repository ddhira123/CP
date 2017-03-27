#include <cstdio>
using namespace std;

int tc;
long long a,b;

long long gcd(long long i,long long j){
 if(j==0)
  return i;
 return gcd(j,i%j);
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%lld %lld",&a,&b);
  long long n=gcd(a,b);
  while(!(n&1))
   n>>=1;
  if(n==1)
   printf("Y\n");
  else
   printf("N\n");
 }
 return 0;
}