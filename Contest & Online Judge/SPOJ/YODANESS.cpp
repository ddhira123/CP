#include <iostream>
#include <map>
using namespace std;

int bit[30005],n,tc;
string x;
map<string,int> m;

void update(int idx){
 for(int i=idx;i<=n;i+=i&-i)
  bit[i]++;
}

int query(int idx){
 int res=0;
 for(int i=idx;i;i-=i&-i)
  res+=bit[i];
 return res;
}

int main(){
 cin>>tc;
 while(tc--){
  cin>>n;
  m.clear();
  int ans=0;
  for(int a=1;a<=n;a++){
   cin>>x;
   m[x]=a;
   bit[a]=0;
  }
  for(int a=1;a<=n;a++){
   cin>>x;
   ans+=query(n)-query(m[x]);
   update(m[x]);
  }
  cout<<ans<<"\n";
 }
 return 0;
}