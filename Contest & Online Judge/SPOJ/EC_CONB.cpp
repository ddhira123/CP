#include <cstdio>
using namespace std;

int tc,n,ans;

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  if(n&1)
   printf("%d\n",n);
  else{
   ans=0;
   while(n){
    ans<<=1;
    ans|=(n&1);
    n>>=1;
   }
   printf("%d\n",ans);
  }
 }
 return 0;
}