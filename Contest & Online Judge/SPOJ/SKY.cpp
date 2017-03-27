#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second
#define mp make_pair

priority_queue<pair<int,pii> > pq;
int dist[1005][1005],n,sx,sy,tx,ty,a,b,c,arr[1005][1005];
pii adj[4]={mp(-1,0),mp(1,0),mp(0,-1),mp(0,1)};

int main(){
 scanf("%d",&n);
 scanf("%d %d %d %d",&sx,&sy,&tx,&ty);
 scanf("%d %d %d",&a,&b,&c);
 for(int i=1;i<=n;i++)
  for(int j=1;j<=n;j++){
   dist[i][j]=-1;
   arr[i][j]=( ( (LL)(i-1) *(LL)n +(LL)(j-1) ) * (LL)a + (LL)b )%(LL)c;
  }
 dist[sx][sy]=arr[sx][sy];
 pq.push(mp(dist[sx][sy],mp(sx,sy)));
 while(!pq.empty()){
  int dis=pq.top().fi,x=pq.top().se.fi,y=pq.top().se.se;
  pq.pop();
  if(dis==dist[x][y])
   for(int i=0;i<4;i++){
    int nx=x+adj[i].fi,ny=y+adj[i].se;
    if(nx>0 && nx<=n && ny>0 && ny<=n && dist[nx][ny]<min(dis,arr[nx][ny])){
     dist[nx][ny]=min(dis,arr[nx][ny]);
     pq.push(mp(dist[nx][ny],mp(nx,ny)));
    }
   }
 }
 printf("%d\n",arr[sx][sy]+arr[tx][ty]-2*dist[tx][ty]);
 return 0;
}
