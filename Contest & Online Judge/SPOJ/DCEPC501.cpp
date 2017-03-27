#include <cstdio>
#include <algorithm>
using namespace std;

long long dp[100005];
int n,tc,arr[100005];

long long solve(int pos){
 if(dp[pos]!=-1)
  return dp[pos];
 long long jum=0;
 dp[pos]=0;
 for(int i=1;i<=min(3,n-pos);i++){
  jum+=arr[pos+i-1];
  dp[pos]=max(dp[pos],jum+solve(min(n,pos+2*i) ));
 }
 return dp[pos];
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(int a=0;a<n;a++){
   scanf("%d",&arr[a]);
   dp[a]=-1;
  }
  dp[n]=0;
  printf("%lld\n",solve(0));
 }
 return 0;
}