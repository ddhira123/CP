#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define fi first
#define se second
#define mp make_pair
typedef pair<int,int> pii;
int dp[1<<15],n;
vector<pii> adj[20];

int solve(int x){
 if(dp[x]!=-1)
  return dp[x];
 for(int i=0;i<15;i++)
  if(x&(1<<i))
   for(int j=0;j<adj[i].size();j++)
    if((x&(1<<adj[i][j].fi))&&!(x&(1<<adj[i][j].se))){
        if(solve(x^(1<<i)^(1<<adj[i][j].fi)^(1<<adj[i][j].se)))
         return dp[x]=1;
       }
  return dp[x]=0;
}

int main(){
 adj[0].push_back(mp(1,3)); adj[0].push_back(mp(2,5)); 
 adj[1].push_back(mp(3,6)); adj[1].push_back(mp(4,8));
 adj[2].push_back(mp(4,7)); adj[2].push_back(mp(5,9));
 adj[3].push_back(mp(1,0)); adj[3].push_back(mp(4,5)); adj[3].push_back(mp(7,12)); adj[3].push_back(mp(6,10));
 adj[4].push_back(mp(7,11)); adj[4].push_back(mp(8,13));
 adj[5].push_back(mp(2,0)); adj[5].push_back(mp(4,3)); adj[5].push_back(mp(8,12)); adj[5].push_back(mp(9,14));
 adj[6].push_back(mp(3,1)); adj[6].push_back(mp(7,8));
 adj[7].push_back(mp(4,2)); adj[7].push_back(mp(8,9));
 adj[8].push_back(mp(4,1)); adj[8].push_back(mp(7,6));
 adj[9].push_back(mp(5,2)); adj[9].push_back(mp(8,7));
 adj[10].push_back(mp(6,3)); adj[10].push_back(mp(11,12));
 adj[11].push_back(mp(7,4)); adj[11].push_back(mp(12,13));
 adj[12].push_back(mp(11,10)); adj[12].push_back(mp(7,3));  adj[12].push_back(mp(8,5)); adj[12].push_back(mp(13,14));
 adj[13].push_back(mp(12,11)); adj[13].push_back(mp(8,4));
 adj[14].push_back(mp(13,12)); adj[14].push_back(mp(9,5));
 for(int a=1;a<(1<<15);a++)
  dp[a]=-1;
 for(int a=1;a<(1<<15);a<<=1)
  dp[a]=1;
 scanf("%d",&n);
 int jum=0;
 while(n--){
  int a;
  scanf("%d",&a);
  jum|=(1<<(a-1));
 }
 if(solve(jum))
  printf("yes\n");
 else
  printf("no\n");
 return 0;
}
