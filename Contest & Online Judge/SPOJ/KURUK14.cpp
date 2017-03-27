#include <cstdio>
using namespace std;

int n,arr[1005],l,r,tc;
bool bisa;

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(int a=0;a<n;a++)
   arr[a]=0;
  for(int a=0;a<n;a++){
   scanf("%d",&l);
   arr[l]++;
  }
  l=0;
  r=n-1;
  bisa=1;
  while(l<=r&&bisa){
   bisa&=(arr[l]+arr[r]==2);
   l++;
   r--;
  }
  if(bisa)
   printf("YES\n");
  else
   printf("NO\n");
 }
 return 0;
}
