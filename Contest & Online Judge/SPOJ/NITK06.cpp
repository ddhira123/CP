#include <cstdio>
using namespace std;

int tc,n,a;
long long arr[10005];

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(a=1;a<=n;a++)
   scanf("%lld",&arr[a]);
  bool bisa=1;
  for(a=1;a<n&&bisa;a++){
    arr[a+1]-=arr[a];
    arr[a]=0;
    bisa&=(arr[a+1]>=0);
  }
  bisa&=(arr[n]==0);
  if(bisa)
   printf("YES\n");
  else
   printf("NO\n");
 }
 return 0;
}
