#include <cstdio>
using namespace std;
int tc,sum,x;

int main(){
 scanf("%d",&tc);
 while(tc--){
  sum=0;
  scanf("%d",&x);
  while(x>0){
   sum+=(x/5);
   x/=5;
  }
  printf("%d\n",sum);
 }
 return 0;
}
