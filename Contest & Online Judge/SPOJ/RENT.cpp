#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
using namespace std;

int dp[10005],tc,n;
pair<pii,int> arr[10005];

int PlayDP(int pos){
 if(dp[pos]!=-1) return dp[pos];
 dp[pos]=PlayDP(pos+1);
 dp[pos]=max(dp[pos],arr[pos].se+PlayDP(lower_bound(arr,arr+n+1,mp(mp(arr[pos].fi.fi+arr[pos].fi.se,0),0))-arr));
 return dp[pos];
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(int i=0;i<n;i++)
   scanf("%d %d %d",&arr[i].fi.fi,&arr[i].fi.se,&arr[i].se),dp[i]=-1;
  arr[n]=mp(mp(1000000000,0),0);
  dp[n]=0;
  sort(arr,arr+n+1);
  printf("%d\n",PlayDP(0));
 }
 return 0;
}