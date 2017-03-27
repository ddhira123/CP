#include <cstdio>
using namespace std;

long long bit[1000005],tc,n,a,res;

int main(){
 scanf("%lld",&tc);
 while(tc--){
  for(a=1;a<=1000001;a++)
   bit[a]=0;
  res=0;
  scanf("%lld",&n);
  while(n--){
   scanf("%lld",&a);
   a++;
   for(long long b=a-1;b;b-=b&-b)
    res+=bit[b];
   for(long long b=a;b<=1000001;b+=b&-b)
    bit[b]+=(a-1);
   //printf("%lld\n",res);
  }
  printf("%lld\n",res);
 }
 return 0;
}