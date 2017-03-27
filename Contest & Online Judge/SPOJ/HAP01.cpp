#include <cstdio>
#include <algorithm>
using namespace std;
typedef unsigned long long LLU;
int tc,a[2],k,ans;
LLU n,m,i,j;
bool cnt;

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%llu %llu %d",&n,&m,&k);
  ans=0;
  for(i=n;i<=m;i++){
   j=i;
   a[0]=a[1]=0;
   cnt=0;
   while(j){
    a[cnt]+=(j&1);
    cnt=1-cnt;
    j>>=1;
   }
   if(abs(a[0]-a[1])==k)
    ans++;
  }
  printf("%d\n",ans);
 }
 return 0;
}
