#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define INF 2000000000000000000LL
#define max_n 30005
long long dp[max_n],dp2[max_n];
vector<int> adj[max_n],adj2[max_n];
int n,s,a,b;


#define g getchar_unlocked
inline int io(){
 register char c;
 while(1){
    c=g();
    if((c^32) && (c^10)) break;
 }
 register int res=c-'0';
 while(1){
  c=g();
  if(!(c^32) || !(c^10))
  return res;
  res=(res<<3)+(res<<1)+(c-'0');
  }
}




long long solve(int pos){
 if(dp[pos]!=-1) return dp[pos];
 dp[pos]=0;
 for(int i=0;i<adj[pos].size();i++)
  dp[pos]+=solve(adj[pos][i]);
 return dp[pos];
}

long long solve2(int pos){
 if(dp2[pos]!=-1) return dp2[pos];
 dp2[pos]=-INF;
 for(int i=0;i<adj2[pos].size();i++)
  dp2[pos]=max(dp2[pos],solve2(adj2[pos][i]));
 dp2[pos]+=solve(pos);
 return dp2[pos];
}

int main(){
 n=io(); s=io();
 for(int i=1;i<=n;i++)
  dp[i]=dp2[i]=-1;
 dp[n]=1;
 while(s--){
  a=io(); b=io();
  adj[a].push_back(b);
  adj2[b].push_back(a);
 }
 dp2[1]=solve(1);
 printf("%lld\n",solve2(n));
 return 0;
}




