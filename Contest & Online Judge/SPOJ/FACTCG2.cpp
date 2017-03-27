#include <cstdio>
using namespace std;

int prim[10000005],n;

int main(){
 for(int a=2;a<=10000000;a++)
  if(!prim[a]){
   for(int b=1;b<=10000000/a;b++)
    if(!prim[a*b])
     prim[a*b]=a;
  }
 while(scanf("%d",&n)==1){
  printf("1");
  while(n>1){
   printf(" x %d",prim[n]);
   n/=prim[n];
  }
  printf("\n");
 }
 return 0;
}
