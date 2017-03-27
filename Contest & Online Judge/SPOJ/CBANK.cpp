#include <cstdio>
#define MOD 1000000007LL

long long arr[4];
int n,tc;

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);n++;
  for(int a=0;a<3;a++)
   arr[a]=n+a;
  if(arr[0]%2==0)
   arr[0]/=2;
  else if(arr[1]%2==0)
   arr[1]/=2;
  else
   arr[2]/=2;
  if(arr[0]%3==0)
   arr[0]/=3;
  else if(arr[1]%3==0)
   arr[1]/=3;
  else
   arr[2]/=3;
  long long ans=1;
  for(int a=0;a<3;a++)
   ans=(ans*arr[a])%MOD;
  printf("%lld\n",ans);
 }
 return 0;
}