#include <cstdio>
#include <vector>
#include <bitset>
#include <queue>
using namespace std;
#define INF 1000000000

bitset<205> visited;
int res[205][205],n,m,a,tc,ans,f,par[205];
vector<int> adj[205];
queue<int> q;

inline void reset(int x){
 for(int i=1;i<=x;i++){
  adj[i].clear();
  for(int j=1;j<=x;j++)
   res[i][j]=0;
 }
}

void PlayAugment(int node,int MinEdge){
 if(node==1){
  f=MinEdge;
  return;
 }
 else if(par[node]!=-1){
  PlayAugment(par[node],min(MinEdge,res[par[node]][node]));
  res[par[node]][node]-=f; res[node][par[node]]+=f;
 }
}

inline void PlayEdKarp(){
 ans=0;
 while(1){
  f=0;
  visited.reset();
  for(int i=1;i<=n;i++)
   par[i]=-1;
  visited[1]=1;
  q.push(1);
  while(!q.empty()){
   int node=q.front(); q.pop();
   if(node==n) break;
   for(int i=0;i<adj[node].size();i++){
    int next=adj[node][i];
    if(res[node][next] > 0 && !visited[next])
     visited[next]=1,q.push(next),par[next]=node;
   }
  }
  while(!q.empty()) q.pop();
  PlayAugment(n,INF);
  if(f==0) break;
  else ans+=f;
 }
 printf("%d\n",ans);
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  reset(n);
  for(int i=1;i<n;i++){
   scanf("%d",&m);
   while(m--){
    scanf("%d",&a);
    adj[i].push_back(a);
    adj[a].push_back(i);
    if(i==1 || a==n)
     res[i][a]=1;
    else
     res[i][a]=INF;
   }
  }
  PlayEdKarp();
 }
 return 0;
}
