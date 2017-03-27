#include <cstdio>
using namespace std;
#define max_n 10000000LL
bool shieve[max_n+5];
long long a[max_n+5];
int prim[max_n+5],tc,x;

int main(){
 for(long long i=2;i<=max_n;i++)
  if(!shieve[i]){
   prim[i]=i;
   for(long long j=i*i;j<=max_n;j+=i){
    shieve[j]=1;
    if(prim[j]==0) prim[j]=i;
   }
  }
 for(int i=2;i<=max_n;i++)
  a[i]=a[i-1]+(long long)prim[i];
 scanf("%d",&tc);
 while(tc--)
  scanf("%d",&x),printf("%lld\n",a[x]);
 //puts("ayaz\n");
 return 0;
}