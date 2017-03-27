#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
typedef pair<long long,long long>pll;
#define fi first
#define se second
#define mp make_pair
#define INF 10000000000LL
pii arr[85];
pll dp[85][10005];
int n,l;

pll solve(int pos,int left){
 if(left<=0)
  return mp(-left,0LL);
 if(pos==n)
  return mp(-INF,-INF);
 if(dp[pos][left].fi!=-1) return dp[pos][left];
 pll tmp,tmp2,ret;
 tmp=solve(pos+1,left);
 tmp2=solve(pos+1,left-arr[pos].fi); tmp2.se+=arr[pos].se;
 if(tmp.fi<tmp2.fi && tmp.fi>=0LL)  ret=tmp;
 else if(tmp.fi>tmp2.fi && tmp2.fi>=0LL) ret=tmp2;
 else if(tmp.se>=tmp2.se) ret=tmp;
 else                    ret=tmp2;
 return dp[pos][left]=ret;
}

int main(){
 scanf("%d %d",&n,&l);
 for(int i=0;i<n;i++){
  scanf("%d %d",&arr[i].fi,&arr[i].se);
  for(int j=0;j<=l;j++)
   dp[i][j]=mp(-1,-1);
 }
 sort(arr,arr+n);
 pll ans=solve(0,l);
 printf("%lld\n",ans.se);
 return 0;
}