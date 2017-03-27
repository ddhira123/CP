#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define INF 1000000000
vector<pii> v;
pii x;
queue<pii> q;
int dist[105][105],r,c,sum,ans,tc;
char z[105];
inline void PlayBFS(pii start){
 dist[start.fi][start.se]=0;
 q.push(start);
 while(!q.empty()){
  pii now=q.front(); q.pop();
  if(now.fi>0 && dist[now.fi-1][now.se]==INF){
   dist[now.fi-1][now.se]=dist[now.fi][now.se]+1;
   q.push(mp(now.fi-1,now.se));
  }
  if(now.fi<r-1 && dist[now.fi+1][now.se]==INF){
   dist[now.fi+1][now.se]=dist[now.fi][now.se]+1;
   q.push(mp(now.fi+1,now.se));
  }
  if(now.se>0 && dist[now.fi][now.se-1]==INF){
   dist[now.fi][now.se-1]=dist[now.fi][now.se]+1;
   q.push(mp(now.fi,now.se-1));
  }
  if(now.se<c-1 && dist[now.fi][now.se+1]==INF){
   dist[now.fi][now.se+1]=dist[now.fi][now.se]+1;
   q.push(mp(now.fi,now.se+1));
  }
 }
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  v.clear();
  scanf("%d %d",&r,&c);
  for(int i=0;i<r;i++){
   scanf("%s",z);
   for(int j=0;j<c;j++){
    if(z[j]=='C')
     x=mp(i,j);
    else if(z[j]=='S')
     v.push_back(mp(i,j));
    if(z[j]=='#')
     dist[i][j]=-1;
    else
     dist[i][j]=INF;
   }
  }
  PlayBFS(x);
  sum=0;
  for(int i=0;i<v.size();i++)
   sum+=2*dist[v[i].fi][v[i].se];
  ans=sum;
  for(int i=0;i<v.size();i++)
   ans=min(ans,sum-dist[v[i].fi][v[i].se]);
  ans+=60*v.size();
  printf("%d\n",ans);
 }
 return 0;
}
