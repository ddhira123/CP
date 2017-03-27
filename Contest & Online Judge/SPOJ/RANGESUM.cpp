#include <cstdio>
#include <algorithm>
using namespace std;

long long prefix[200005],arr[100005],n,q,siz,a,b,op;

int main(){
 scanf("%lld",&n);
 for(int i=1;i<=n;i++)
  scanf("%lld",&arr[i]);
 reverse(arr+1,arr+n+1);
 for(int i=1;i<=n;i++)
  prefix[i]=prefix[i-1]+arr[i];
 siz=n;
 scanf("%lld",&q);
 while(q--){
  scanf("%lld",&op);
  if(op==2){
   scanf("%lld",&a);
   siz++;
   prefix[siz]=prefix[siz-1]+a;
  }
  else{
   scanf("%lld %lld",&a,&b);
   a=siz-a+1;
   b=siz-b;
   printf("%lld\n",prefix[a]-prefix[b]);
  }
 }
 return 0;
}