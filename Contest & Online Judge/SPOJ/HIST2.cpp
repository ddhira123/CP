#include <cstdio>
#include <algorithm>
using namespace std;
#define fi first
#define se second
#define mp make_pair
typedef pair<int,long long> pil;

pil dp[16][(1<<15)+1];
int tgt,n,arr[16],a,b;

pil solve(int last,int bit){
 if(bit==tgt)
  return mp(2*n+arr[last],1);
 if(dp[last][bit].fi!=-1)
  return dp[last][bit];
 pil res=mp(-1,-1);
 for(int i=0;i<n;i++)
  if(!(bit&(1<<i))){
   pil tmp=solve(i+1,bit|(1<<i));
   tmp.fi+=abs(arr[last]-arr[i+1]);
   if(tmp.fi>res.fi)
    res=tmp;
   else if(tmp.fi==res.fi)
    res.se+=tmp.se;
  }
 return dp[last][bit]=res;
}

int main(){
 scanf("%d",&n);
 while(n){
  for(a=1;a<=n;a++)
   scanf("%d",&arr[a]);
  arr[0]=0;
  tgt=(1<<n)-1;
  for(a=0;a<=n;a++)
   for(b=0;b<=tgt;b++)
    dp[a][b]=mp(-1,-1);
  pil ans=solve(0,0);
  printf("%d %lld\n",ans.fi,ans.se);
  scanf("%d",&n);
 }
 return 0;
}
