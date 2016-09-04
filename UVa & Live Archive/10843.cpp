#include <iostream>
using namespace std;
typedef long long LL;

LL mod=2000000011;
int tc,n;
int ans[105];

int modpow(LL base,int po){
 LL res=1;
 while(po){
  if(po&1) res=(res*base)%mod;
  po>>=1;
  base=(base*base)%mod;
 }
 return res;
}

int main(){
 for(int i=1;i<=100;i++)
  ans[i]=-1;
 ans[1]=1;
 ios_base::sync_with_stdio(false);
 cin>>tc;
 for(int t=1;t<=tc;t++){
  cin>>n;
  if(ans[n]==-1) ans[n]=modpow(n,n-2);
  cout<<"Case #"<<t<<": "<<ans[n]<<"\n";
 }
 return 0;
}
