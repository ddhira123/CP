#include <cstdio>
#include <vector>
#include <queue>
#include <bitset>
#include <algorithm>
using namespace std;
#define INF 1000000000
#define N 2005

int par[2020],res[2020][2020],ans,f,s,t,m,n,a,b;
vector<int> adj[2020];
queue<int> q;

inline void MaxFlow(){
 ans=0;
 while(1){
  f=0;
  for(int i=0;i<2020;i++)
   par[i]=-1;
  //printf("%d\n",!visited[1]);
  par[s+1005]=0;
  q.push(s+1005);
  while(!q.empty()){
   int now=q.front(); q.pop();
   for(int i=0;i<adj[now].size();i++){
    int next=adj[now][i];
    if(res[now][next] > 0 && par[next]==-1)
     q.push(next),par[next]=now;
   }
  }
  if(par[t]==-1) break;
  else{
   int now=t;
   while(now){
    res[par[now]][now]--;
    res[now][par[now]]++;
    now=par[now];
   }
  }
  ans++;
 }
 //for(int i=1;i<=n;i++)
  //if(res[2*i][2*i+1]==0) printf("%d\n",i);
 printf("%d\n",ans);
}

int main(){
 scanf("%d %d",&n,&m);
 scanf("%d %d",&s,&t);
 while(m--){
  scanf("%d %d",&a,&b);
  adj[a+1005].push_back(b);
  adj[a].push_back(b+1005);
  adj[b].push_back(a+1005);
  adj[b+1005].push_back(a);
  res[a+1005][b]=1;
  res[b+1005][a]=1;
 }
 for(int i=1;i<=n;i++){
  adj[i].push_back(i+1005);
  adj[i+1005].push_back(i);
  res[i][i+1005]=1;
  res[i+1005][i]=1;
 }
 MaxFlow();
 return 0;
}