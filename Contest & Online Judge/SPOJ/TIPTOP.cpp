#include <cstdio>
using namespace std;

long long l,r,m,n;
int tc,i;
int main(){
 scanf("%d",&tc);
 for(i=1;i<=tc;i++){
  scanf("%lld",&n);
  l=1;r=1000000000;
  while(l<r){
   m=(l+r)/2;
   if(m*m>=n)
    r=m;
   else
    l=m+1;
  }
  printf("Case %d: ",i);
  if(l*l==n)
   printf("Yes\n");
  else
   printf("No\n");
 }
 return 0;
}
