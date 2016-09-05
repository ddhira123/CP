#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

map<string,int> ms;
string s,p,arr[105];
int n,m,tc;
int deg[105];
vector<int> adj[105];

inline void TopoSort(){
 priority_queue<int> pq;
 for(int i=0;i<n;i++)
  if(deg[i]==0) pq.push(-i);
 while(!pq.empty()){
  int cur=-pq.top();
  pq.pop();
  cout<<" "<<arr[cur];
  for(int i=0;i<adj[cur].size();i++){
   int nxt=adj[cur][i];
   deg[nxt]--;
   if(deg[nxt]==0) pq.push(-nxt);
  }
 }
 cout<<".\n\n";
}

int main(){
 ios_base::sync_with_stdio(false);
 while(cin>>n){
  ms.clear();
  for(int i=0;i<n;i++)
   cin>>arr[i],adj[i].clear(),ms[arr[i]]=i;
  cin>>m;
  while(m--){
   cin>>s>>p;
   int x,y;
   x=ms[s],y=ms[p];
   deg[y]++;
   adj[x].push_back(y);
  }
  cout<<"Case #"<<++tc<<": Dilbert should drink beverages in this order:";
  TopoSort();
 }
 return 0;
}
