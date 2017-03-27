#include <iostream>
using namespace std;

typedef long long LL;

const LL MOD=109546051211LL;
const LL p1=186583;
const LL p2=587117;

int n;
LL in1,in2;

inline LL modpow(LL base,LL po,LL mod){
 LL ans=1;
 while(po){
  if(po&1) ans=(base*ans)%mod;
  po>>=1;
  base=(base*base)%mod;
 }
 return ans;
}

inline LL calc(LL x,LL y,LL mod){
 x%=mod;
 y%=mod;
 x=(x*y)%mod;
 return x;
}

int main(){
 in1=modpow(p1,p2-2,p2);
 in2=modpow(p2,p1-2,p1);
 cin>>n;
 LL ans=1;
 if(n>=p2) ans=0;
 else{
  LL fak=1;
  for(int i=1;i<=n;i++){
   fak=calc(fak,i,MOD);
   LL ret1=calc(ans,fak,p1);
   ret1=calc(ret1,p2,MOD);
   ret1=calc(ret1,in2,MOD);
   LL ret2=calc(ans,fak,p2);
   ret2=calc(ret2,p1,MOD);
   ret2=calc(ret2,in1,MOD);
   ans=(ret1+ret2)%MOD;
  }
 }
 cout<<ans<<"\n";
 return 0;
}
