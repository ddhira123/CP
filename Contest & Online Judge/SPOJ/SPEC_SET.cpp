#include <cstdio>
using namespace std;

int main(){
 int tc;
 scanf("%d",&tc);
 while(tc--){
  int n,k,ans;
  scanf("%d %d",&n,&k);
  if(k==1) puts("0");
  else{
   ans=0;
   for(int i=1;n;i=-i){
    ans+=n*i;
    n/=k;
   }
   printf("%d\n",ans);
  }
 }
 return 0;
}
