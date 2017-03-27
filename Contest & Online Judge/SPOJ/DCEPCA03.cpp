#include <cstdio>
using namespace std;

bool flag[10005];
long long tot[10005],prefix[10005],a,b,tc;

int main(){
 for(a=1;a<=10000;a++)
  tot[a]=a;
 for(a=2;a<=10000;a++)
  if(!flag[a]){
   tot[a]=a-1;
   for(b=2;b<=10000/a;b++){
    flag[a*b]=1;
    tot[a*b]-=(tot[a*b]/a);
   }
  }
 for(a=1;a<=10000;a++)
  prefix[a]=prefix[a-1]+tot[a];
 scanf("%lld",&tc);
 while(tc--){
  scanf("%lld",&a);
  printf("%lld\n",prefix[a]*prefix[a]);
 }
 return 0;
}