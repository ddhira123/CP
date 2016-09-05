#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

vector<int> v,lis;
int x,tc;
bool flag;

int main(){
 ios_base::sync_with_stdio(0);
 cin>>x;
 while(x!=-1){
  if(flag) cout<<"\n";
  else flag=1;
  v.clear();
  lis.clear();
  v.push_back(x);
  cin>>x;
  while(x!=-1){
   v.push_back(x);
   cin>>x;
  }
  assert(v.size()<100000);
  for(int i=v.size()-1;i>=0;i--){
   if(lis.empty() || lis.back()<=v[i]) lis.push_back(v[i]);
   else{
    int lo=0,hi=lis.size()-1;
    while(lo<hi){
     int mi=(lo+hi)>>1;
     if(v[i] >= lis[mi]) lo=mi+1;
     else hi=mi;
    }
    lis[lo]=v[i];
   }
  }
  cout<<"Test #"<<++tc<<":\n";
  cout<<"  maximum possible interceptions: "<<(int)lis.size()<<"\n";
  cin>>x;
 }
 return 0;
}
