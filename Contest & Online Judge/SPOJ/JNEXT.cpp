#include <cstdio>
#include <algorithm>
using namespace std;

int arr[1000005],n,tc,a;

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(a=0;a<n;a++)
   scanf("%d",&arr[a]);
  if(next_permutation(arr,arr+n)){
   for(a=0;a<n;a++)
    printf("%d",arr[a]);
   printf("\n");
  }
  else
   printf("-1\n");
 }
 return 0;
}
