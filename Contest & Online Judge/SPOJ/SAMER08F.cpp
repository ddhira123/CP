#include <cstdio>
using namespace std;

int dp[105],a;

int main(){
 for(a=1;a<=100;a++)
  dp[a]=dp[a-1]+a*a;
 scanf("%d",&a);
 while(a){
  printf("%d\n",dp[a]);
  scanf("%d",&a);
 }
 return 0;
}
