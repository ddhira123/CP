#include <cstdio>
using namespace std;

int arr[100005],n,a;

int main(){
 scanf("%d",&n);
 while(n){
  for(a=1;a<=n;a++)
   scanf("%d",&arr[a]);
  bool bisa=1;
  for(a=1;a<=n&&bisa;a++)
   bisa&=(arr[arr[a]]==a);
  if(bisa)
   printf("ambiguous\n");
  else
   printf("not ambiguous\n");
  scanf("%d",&n);
 }
 return 0;
}
