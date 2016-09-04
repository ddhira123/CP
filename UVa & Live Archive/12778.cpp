#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair

pii arr[50005];
set<int> S;
int n,tc;

int main(){
 ios_base::sync_with_stdio(false);
 cin>>tc;
 for(int t=1;t<=tc;t++){
  S.clear();
  LL ans=0;
  cin>>n;
  for(int i=0;i<n;i++)
   cin>>arr[i].fi,arr[i].se=i;
  sort(arr,arr+n);
  S.insert(-1);
  S.insert(n);
  for(int i=0;i<n;i++){
   int id=arr[i].se;
   int val=arr[i].fi;
   ans+=(LL)(id+1)*(LL)(n-id)*(LL)(val);
   set<int>::iterator it=S.lower_bound(id);
   int rig=*it;
   it--;
   int le=*it;
   rig--;
   le++;
   ans-=(LL)(val)*(LL)(id-le+1)*(LL)(rig-id+1)*(LL)(rig-id+2)/2LL;
   ans-=(LL)(val)*(LL)(rig-id+1)*(LL)(id-le)*(LL)(id-le+1)/2LL;
   //cout<<val<<" "<<id<<" "<<ans<<"\n";
   S.insert(id);
  }
  cout<<"Case "<<t<<": "<<ans<<"\n";
 }
 return 0;
}
