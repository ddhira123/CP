#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <cstdlib>
#include <cassert>
using namespace std;
typedef pair<int,int> pii;
#define INF 1000000000
#define EPS 1e-9
#define fi first
#define se second
#define mp make_pair
 
int r,c,ans,f,cnt,tc;
char x[45][45];
int par[90],lvl[90],flow[90][90];
vector<int> adj[90];
queue<int> q;
 
void augment(int pos,int Min){
 if(pos==0){
  f=Min;
  return;
 }
 else if(Min==0) return;
  augment(par[pos],min(Min,flow[par[pos]][pos]));
  flow[par[pos]][pos]-=f;
  flow[pos][par[pos]]+=f;
}
 
 
 
inline void reset(){
 while(!q.empty()) q.pop();
 for(int i=0;i<=r+c+1;i++){
  lvl[i]=-1;
  par[i]=-1;
 }
}
 
 
inline void PlayBFS(){
 lvl[0]=par[0]=0;
 q.push(0);
 while(!q.empty()){
 int pos=q.front();
 q.pop();
 if(pos==r+c+1) break;
 for(int i=0;i<adj[pos].size();i++){
  int next=adj[pos][i];
  if(lvl[next]==-1 && flow[pos][next]>0)
   lvl[next]=lvl[pos]+1,q.push(next),par[next]=pos;
  }
 }
}
 
 
inline void MakeAdj(){
 for(int i=0;i<=r+c+1;i++)
  adj[i].clear();
  for(int i=1;i<=r;i++)
   for(int j=1;j<=c;j++)
    if(x[i-1][j-1]=='1')
     adj[i].push_back(r+j),adj[r+j].push_back(i);
  for(int i=1;i<=r;i++)
   adj[0].push_back(i),adj[i].push_back(0);
  for(int i=1;i<=c;i++)
   adj[r+i].push_back(r+c+1),adj[r+c+1].push_back(r+i); 
}
 
inline void PlayMax(int z){
  //printf("%c\n",zz);
  for(int i=0;i<=r+c+1;i++)
   for(int j=0;j<=r+c+1;j++)
    flow[i][j]=0;
  cnt=0;
  for(int i=1;i<=r;i++)
   for(int j=0;j<adj[i].size()-1;j++)
    flow[i][adj[i][j]]=1,cnt++;
  for(int i=1;i<=r;i++)
   flow[0][i]=z;
  for(int i=1;i<=c;i++)
   flow[r+i][r+c+1]=(z*r)/c;
  int mf=0;
  //printf("%d\n",cnt);
  while(1){
   reset();
   PlayBFS();
   if(lvl[r+c+1]==-1) break;
   for(int i=0;i<adj[r+c+1].size();i++){
    int prev=adj[r+c+1][i];
    if(lvl[prev]+1==lvl[r+c+1] && flow[prev][r+c+1]){
     f=0;
     augment(prev,flow[prev][r+c+1]);
     flow[prev][r+c+1]-=f;
     flow[r+c+1][prev]+=f;
     mf+=f;
    }
   }
   //ans=min(ans,edgecnt+z*r-2*mf);
  }
  //printf("%d %d\n",z,mf);
   ans=min(ans,cnt+z*r-2*mf);      
   //printf("%d\n",ans);
}
 
 
 
int main(){
 scanf("%d",&tc);
 for(int t=1;t<=tc;t++){
 scanf("%d %d",&r,&c);
 assert(r>=1 && r<=40 && c>=1 && c<=40);
 for(int i=0;i<r;i++)
  scanf("%s",x[i]);
 MakeAdj();
 ans=INF;
 for(int i=0;i<=c;i++)
  if((i*r)%c==0)
  PlayMax(i);
 printf("Case %d: %d\n",t,ans); 
 }
 //puts("ganteng");
 return 0;
}
