#include <cstdio>
using namespace std;

int n,sum,a;

int main(){
 scanf("%d",&n);
 sum=0;
 for(a=1;(n/a)>(a-1);a++){
  sum+=(n/a)-(a-1);
  //printf("%d %d\n",a,sum);
 }
 printf("%d\n",sum);
 return 0;
}