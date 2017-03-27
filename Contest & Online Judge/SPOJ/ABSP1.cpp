#include <cstdio>
#include <algorithm>
using namespace std;
#define mod 1000007LL
long long arr[100005],ans,prefix[100005];
int tc,a,n;
int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(a=1;a<=n;a++)
   scanf("%lld",&arr[a]);
  sort(arr+1,arr+n+1);
  for(a=1;a<=n;a++)
   prefix[a]=prefix[a-1]+arr[a];
  ans=0;
  for(a=1;a<=n;a++)
   ans+=(a-1-n+a)*arr[a]-prefix[a-1]+prefix[n]-prefix[a];
  ans/=2LL;
  printf("%lld\n",ans);
 }
 return 0;
}
