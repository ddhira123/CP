#include <cstdio>
#include <vector>
using namespace std;
#define MOD 1000000007

int dp[10][100001],n,tc,last;
vector<int> adj[10];

inline void gen(int z){
 for(int i=last+1;i<=z;i++)
  for(int j=0;j<10;j++)
    for(int k=0;k<(int)adj[j].size();k++)
     dp[j][i]=(dp[j][i]+dp[adj[j][k]][i-1])%MOD;
 last=z;
}

int main(){
 adj[0].push_back(7);
 adj[1].push_back(2);  adj[1].push_back(4);
 adj[2].push_back(1);  adj[2].push_back(3);  adj[2].push_back(5);
 adj[3].push_back(2);  adj[3].push_back(6);
 adj[4].push_back(7);  adj[4].push_back(1);  adj[4].push_back(5);
 adj[5].push_back(2);  adj[5].push_back(4);  adj[5].push_back(6);  adj[5].push_back(8);
 adj[6].push_back(3);  adj[6].push_back(5);  adj[6].push_back(9);
 adj[7].push_back(0);  adj[7].push_back(4);  adj[7].push_back(8);
 adj[8].push_back(5);  adj[8].push_back(7);  adj[8].push_back(9);
 adj[9].push_back(8);  adj[9].push_back(6);
 for(int i=0;i<10;i++)
  dp[i][1]=1;
 last=1;
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  if(last<n)
   gen(n);
  int ans=0;
  for(int i=0;i<10;i++)
   ans=(ans+dp[i][n])%MOD;
  printf("%d\n",ans);
 }
 return 0;
}
