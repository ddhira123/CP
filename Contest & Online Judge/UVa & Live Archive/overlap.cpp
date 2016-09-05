#include <iostream>
#include <algorithm>
using namespace std;

int dp[7][(1<<6)+5];
string x[10];
int n,tc;
int dist[7][7];
int len[7];

inline int kmp(int l,int m){
 int b[15];
 int i,j;
 b[0]=-1,i=0,j=-1;
 while(i<len[m]){
  while(j>=0 && x[m][j]!=x[m][i]) j=b[j];
  i++;
  j++;
  b[i]=j;
 }
 i=j=0;
 while(i<len[l]){
  while(j>=0 && x[l][i]!=x[m][j]) j=b[j];
  i++;
  j++;
  if(j==len[m]) return 0;
 }
 return len[m]-j;
}

int solve(int pos,int mask){
 if(mask==0) return 0;
 if(dp[pos][mask]!=-1) return dp[pos][mask];
 int ret=1000000000;
 for(int i=0;i<n;i++)
  if(mask&(1<<i)){
   if(dist[pos][i]==0) ret=min(ret,solve(pos,mask^(1<<i)));
   else                ret=min(ret,dist[pos][i]+solve(i,mask^(1<<i)));
  }
 return dp[pos][mask]=ret; 
}

inline void reset(){
 for(int i=0;i<n;i++){
  cin>>x[i];
  len[i]=x[i].length();
  for(int j=0;j<(1<<n);j++)
   dp[i][j]=-1; 
 }
}

inline void build(){
 for(int i=0;i<n;i++)
  for(int j=0;j<n;j++)
   dist[i][j]=kmp(i,j);
}

int main(){
 ios::sync_with_stdio(0);
 cin>>tc;
 for(int t=1;t<=tc;t++){
  cin>>n;
  reset();
  build();
  int ans=1000000000;
  int tgt=(1<<n)-1;
  for(int i=0;i<n;i++)
   ans=min(ans,len[i]+solve(i,tgt^(1<<i)));
  cout<<"Case "<<t<<": "<<ans<<"\n"; 
 }
 return 0;
}
