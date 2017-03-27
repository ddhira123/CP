#include <cstdio>
using namespace std;

int tc,n,a,b;

int convert(int x){
 if(x<0)
  return x;
 if(x==2)
  return -2;
 if(x==1||x==5)
  return -3;
 return -4;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  scanf("%d",&b);
  printf("%d",convert(b));
  for(a=1;a<n;a++){
   scanf("%d",&b);
   printf(" %d",convert(b));
  }
  printf("\n");
 }
 return 0;
}
