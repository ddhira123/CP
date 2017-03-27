#include <cstdio>
using namespace std;
#define max_n 600
#define MOD 1000000007
long long ans,fact[max_n+5],inve[max_n+5];
int jum,n,x[55],z;

inline long long modpow(long long base,int po){
 long long res=1;
 while(po){
  if(po&1) res=(res*base)%MOD;
  base=(base*base)%MOD;
  po>>=1;
 }
 return res;
}

int main(){
 fact[0]=1; inve[0]=1;
 for(int i=1;i<=max_n;i++){
  fact[i]=(fact[i-1]*(long long) i)%MOD;
  inve[i]=modpow(fact[i],MOD-2);
 }
 scanf("%d",&n);
 while(n){
  ans=1;jum=0;
  for(int i=0;i<n;i++)
   scanf("%d",&x[i]);
  for(int i=0;i<n;i++) {
   scanf("%d",&z);
   jum+=z-x[i];
   ans=(ans*inve[z-x[i]])%MOD;
  }
  ans=(ans*fact[jum])%MOD;
  printf("%lld\n",ans);
  scanf("%d",&n);
 }
 return 0;
}