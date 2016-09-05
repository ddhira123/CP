#include <iostream>
#include <algorithm>
using namespace std;
#define fi first
#define se second
#define mp make_pair

string tmp;
pair<string,int> arr[1005],arr2[1005];
pair<int,int> dp[1005][1005];
int tc,n,m;

pair<int,int> Maks(pair<int,int> i,pair<int,int> j){
 if(i.fi>j.fi) return i;
 else if(i.fi < j.fi) return j;
 else if(i.se<=j.se) return i;
 else                return j;
}

int main(){
 ios_base::sync_with_stdio(0);
 cin>>tc;
 while(tc--){
 cin>>n;
 for(int i=0;i<n;i++)
  cin>>tmp>>arr[i].fi>>arr[i].se;
 cin>>m;
 for(int i=0;i<m;i++)
  cin>>tmp>>arr2[i].fi>>arr2[i].se;
 for(int i=0;i<=m;i++)
  dp[n][i]=mp(0,0);
 for(int i=0;i<=n;i++)
  dp[i][m]=mp(0,0);
 for(int i=n-1;i>=0;i--)
  for(int j=m-1;j>=0;j--){
   dp[i][j]=Maks(dp[i+1][j],dp[i][j+1]);
   if(arr[i].fi==arr2[j].fi){
    pair<int,int> dum=dp[i+1][j+1];
    dum.se++;
    dum.fi+=arr[i].se+arr2[j].se;
    dp[i][j]=Maks(dum,dp[i][j]);
   }
  }
  cout<<dp[0][0].fi<<" "<<dp[0][0].se<<"\n";
 }
 return 0;
}
