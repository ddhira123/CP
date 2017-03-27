#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define MOD 100000000

int dp[100005],n,a,b;
vector<pii> v;

int solve(int pos){
 if(dp[pos]!=-1) return dp[pos];
 dp[pos]=solve(pos+1);
 int next=lower_bound(v.begin(),v.end(),mp(v[pos].se,-1))-v.begin();
 dp[pos]=(dp[pos]+solve(next))%MOD;
 return dp[pos];
}

int main(){
 scanf("%d",&n);
 while(n!=-1){
  v.clear();
  for(int i=0;i<n;i++){
   scanf("%d %d",&a,&b);
   v.pb(mp(a,b));
   dp[i]=-1;
  }
  dp[n]=1;
  sort(v.begin(),v.end());
  int ans=solve(0)-1;
  if(ans<0) ans+=MOD;
  printf("%08d\n",ans);
  scanf("%d",&n);
 }
 return 0;
}