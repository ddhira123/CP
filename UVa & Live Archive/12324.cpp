#include <iostream>
using namespace std;

int dp[105][105];
int cost[105],b[105];
int n;

int solve(int pos,int left){
 int &ret=dp[pos][left];
 if(ret!=-1) return ret;
 ret=cost[pos]+solve(pos+1,min(n-pos-1,left+b[pos]));
 if(left)
  ret=min(ret,(cost[pos]>>1)+solve(pos+1,min(n-pos-1,left-1+b[pos])));
 return ret;
}

int main(){
 ios_base::sync_with_stdio(0);
 cin>>n;
 while(n){
  for(int i=0;i<n;i++){
   cin>>cost[i]>>b[i];
   for(int j=n-i;j>=0;j--)
    dp[i][j]=-1;
  }
  dp[n][0]=0;
  cout<<solve(0,0)<<"\n";
  cin>>n;
 }
 return 0;
}
