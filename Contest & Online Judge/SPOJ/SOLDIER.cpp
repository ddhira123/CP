#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

vector<pair<int,int> > lis[10];
int n,t,dp[10][1005],a,b,c;

int solve(int pos,int left){
 if(pos==7)
  return 1000000000;
 if(dp[pos][left]!=-1)
  return dp[pos][left];
 dp[pos][left]=0;
 for(int i=0;i<lis[pos].size();i++)
  if(left>=lis[pos][i].first)
   dp[pos][left]=max(dp[pos][left],min(lis[pos][i].second,solve(pos+1,left-lis[pos][i].first)));
  return dp[pos][left];
}

int main(){
 memset(dp,-1,sizeof dp);
 scanf("%d %d",&n,&t);
 while(n--){
  scanf("%d%d%d",&a,&b,&c);
  lis[a].push_back(make_pair(b,c));
 }
 printf("%d\n",solve(1,t));
 return 0;
}
