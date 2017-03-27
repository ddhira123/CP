#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

int tc,i,n,k,a,b,flag[2005];
vector<int> adj[2005];
queue<int> q;

int main(){
 scanf("%d",&tc);
 for(i=1;i<=tc;i++){
  scanf("%d %d",&n,&k);
  for(a=1;a<=n;a++){
   flag[a]=-1;
   adj[a].clear();
  }
  while(k--){
   scanf("%d %d",&a,&b);
   adj[a].push_back(b);
   adj[b].push_back(a);
  }
  bool bisa=1;
  for(a=1;a<=n;a++)
   if(flag[a]==-1){
    flag[a]=1;
    q.push(a);
    while(!q.empty()){
     int node=q.front();
     q.pop();
     for(b=0;b<adj[node].size();b++)
      if(flag[adj[node][b]]==-1){
        flag[adj[node][b]]=1-flag[node];
        q.push(adj[node][b]);
      }
      else if (flag[node]==flag[adj[node][b]])
       bisa=0;
    }
   }
  printf("Scenario #%d:\n",i);
  if(bisa)
   printf("No suspicious bugs found!\n");
  else
   printf("Suspicious bugs found!\n");
 }
 return 0;
}
