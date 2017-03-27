#include <cstdio>
#include <vector>
#include <bitset>
#include <algorithm>
#include <queue>
using namespace std;
#define INF 1000000000
#define MAXN 55

bitset<MAXN> visited;
vector<int> adj[MAXN];
int res[MAXN][MAXN],n,a,par[MAXN],f,ans;
char x[5],y[5];
queue<int> q;

inline int convert(char z){
 if(z>='a') return z-'a';
 return z-'A'+26;
}

void PlayAugment(int node,int MinEdge){
 if(node==26){
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
  for(int i=0;i<MAXN;i++)
   par[i]=-1;
  visited[26]=1;
  q.push(26);
  while(!q.empty()){
   int node=q.front(); q.pop();
   //printf("%d\n",node);
   if(node==51) break;
   for(int i=0;i<adj[node].size();i++){
    int next=adj[node][i];
    if(res[node][next] > 0 && !visited[next])
     visited[next]=1,q.push(next),par[next]=node;
   }
  }
  while(!q.empty()) q.pop();
  PlayAugment(51,INF);
  //printf("%d\n",f);
  if(f==0) break;
  else ans+=f;
 }
 printf("%d\n",ans);
}

int main(){
 scanf("%d",&n);
 while(n--){
  scanf("%s %s %d",x,y,&a);
  int i,j;
  i=convert(x[0]);
  j=convert(y[0]);
  adj[i].push_back(j);
  adj[j].push_back(i);
  //printf("%d %d\n",i,j);
  res[i][j]+=a;
  res[j][i]+=a;
 }
 PlayEdKarp();
 return 0;
}
