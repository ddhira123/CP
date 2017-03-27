#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> tmp[1005],v[1005];
long long dp[1005][3],ans;
int n,m,freq[1000005];

long long solve(int pos,int left){
 if(pos<left)
  return 0;
 if(left==0)
  return 1;
 if(dp[pos][left]!=-1)
  return dp[pos][left];
 return dp[pos][left]=solve(pos-1,left)+solve(pos-1,left-1);
}

int main(){
 scanf("%d %d",&n,&m);
 for(int a=0;a<3;a++)
  for(int b=0;b<=n;b++)
   dp[b][a]=-1;
 while(m--){
  int a,b;
  scanf("%d %d",&a,&b);
  tmp[a-1].push_back(b-1);
 }
 for(int a=0;a<n;a++)
  if(!tmp[a].empty()){
   sort(tmp[a].begin(),tmp[a].end());
   v[a].push_back(tmp[a][0]);
   for(int b=1;b<tmp[a].size();b++)
    if(tmp[a][b]!=tmp[a][b-1])
     v[a].push_back(tmp[a][b]);
  }
 for(int a=0;a<n;a++)
  for(int b=0;b<v[a].size();b++)
   for(int c=b+1;c<v[a].size();c++)
    freq[v[a][b]+1000*v[a][c]]++;
 for(int a=0;a<=1000000;a++)
  ans+=solve(freq[a],2);
 printf("%lld\n",ans);
 return 0;
}