#include <queue>
#include <cstdio>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
int arr[55][55],tc,n,sx,sy,ex,ey;
bool visited[55][55][1025];
pii path[4]={mp(1,0),mp(0,1),mp(-1,0),mp(0,-1)};
queue<pair<pii,int> > q;

inline bool isvalid(int rr,int cc,int mask){
 if(rr>=0 && rr<n && cc>=0 && cc<n)
  return !visited[rr][cc][mask|(1<<arr[rr][cc])];
 return 0;
}

inline void PlayBFS(){
 q.push(mp(mp(sx,sy),1<<arr[sx][sy]));
 visited[sx][sy][1<<arr[sx][sy]]=1;
 while(!q.empty()){
  int nowx=q.front().fi.fi,nowy=q.front().fi.se,nowmask=q.front().se;
  q.pop();
  for(int i=0;i<4;i++)
   if (isvalid(nowx+path[i].fi,nowy+path[i].se,nowmask)){
    int nextx=path[i].fi+nowx,nexty=nowy+path[i].se,nextm=nowmask|(1<<arr[nextx][nexty]);
    q.push(mp(mp(nextx,nexty),nextm));
    visited[nextx][nexty][nextm]=1;
   }
 }
}

inline int countbit(int x){
 int res=0;
 while(x){
  res++;
  x&=(x-1);
 }
 return res;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(int i=0;i<n;i++)
   for(int j=0;j<n;j++){
    scanf("%d",&arr[i][j]);
    for(int k=0;k<1024;k++)
     visited[i][j][k]=0;
   }
  scanf("%d %d",&sx,&sy);
  scanf("%d %d",&ex,&ey);
  PlayBFS();
  int ans=100;
  for(int i=0;i<1024;i++)
   if(visited[ex][ey][i])
    ans=min(ans,countbit(i));
  printf("%d\n",ans);
 }
 return 0;
}
