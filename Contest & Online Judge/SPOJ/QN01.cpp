#include <cstdio>
using namespace std;

int prefix[1005],n,a,maks,ki,ka;

int main(){
 scanf("%d",&n);
 for(int i=1;i<=n;i++){
  scanf("%d",&a);
  prefix[i]=prefix[i-1]^a;
 }
 maks=-1;
 for(int i=1;i<=n;i++)
  for(int j=i;j<=n;j++)
   if((prefix[i-1]^prefix[j])>maks){
    maks=prefix[i-1]^prefix[j];
    ki=i;
    ka=j;
   }
 printf("%d\n%d %d\n",maks,ki,ka);
 return 0;
}
