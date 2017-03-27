#include <cstdio>
using namespace std;

int ans,nim,arr[1005],tc,i,n,a;

int main(){
 scanf("%d",&tc);
 for(int i=1;i<=tc;i++){
  nim=ans=0;
  scanf("%d",&n);
  for(a=0;a<n;a++){
   scanf("%d",&arr[a]);
   nim^=arr[a];
  }
  for(a=0;a<n;a++)
   ans+=(arr[a]>(nim^arr[a]));
  printf("Case %d: %d\n",i,ans);
 }
 return 0;
}
