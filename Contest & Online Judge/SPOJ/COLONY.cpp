#include <cstdio>
using namespace std;

int main(){
 int y;
 long long n;
 bool ans,arr[60];
 scanf("%d",&y);
 scanf("%lld",&n);
 for(int a=0;a<y;a++){
  arr[a]=n&1;
  n>>=1;
 }
 ans=1;
 for(int a=y-1;a>=0;a--)
  if(!arr[a])
   ans=!ans;
 if(ans)
  printf("red\n");
 else
  printf("blue\n");
 return 0;
}
