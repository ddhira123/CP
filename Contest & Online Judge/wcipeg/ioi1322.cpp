#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int rais[50005];
int ano[50005];
int a,b,n;
pair<int,int> arr[1000005];

bool valid(int x){
 priority_queue<int> pq;
 int it=0,it2;
 for(int i=0;i<a;i++){
  while(it < n && arr[it].first < ano[i])
   pq.push(arr[it].second),it++;
  it2=x;
  while(!pq.empty() && it2>0) pq.pop(),it2--;
 }
 while(it<n) pq.push(arr[it].second),it++;
 for(int i=b-1;i>=0;i--){
  it2=x;
  while(!pq.empty() && pq.top() < rais[i] && it2>0) pq.pop(),it2--;
 }
 return pq.empty();
}

int main(){
 ios_base::sync_with_stdio(0);
 cin>>a>>b>>n;
 int wmaks=-1,smaks=-1;
 for(int i=0;i<a;i++)
  cin>>ano[i],wmaks=max(wmaks,ano[i]);
 for(int i=0;i<b;i++)
  cin>>rais[i],smaks=max(smaks,rais[i]);
 //cout<<wmaks<<" "<<smaks<<"\n";
 bool bol=1;
 for(int i=0;i<n;i++){
  cin>>arr[i].first>>arr[i].second;
  if(arr[i].first >= wmaks && arr[i].second >= smaks){
   bol=0;
  }
 }
 if(bol){
 sort(ano,ano+a);
 sort(rais,rais+b);
 sort(arr,arr+n);
 int lo=1,hi=n;
 while(lo<hi){
  int mi=(lo+hi)>>1;
  if(valid(mi)) hi=mi;
  else lo=mi+1;
 }
 cout<<lo<<"\n";
 }
 else
  cout<<"-1\n";
 return 0;
}

