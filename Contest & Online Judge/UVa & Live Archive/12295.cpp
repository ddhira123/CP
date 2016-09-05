#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair

const int mod=1000000009;
const int INF=1000000000;

int dist[105][105],dp[105][105];
int arr[105][105];
int n,tc;
priority_queue<pair<int,pii> > pq;
int dr[4]={-1,0,1,0},dc[4]={0,-1,0,1};

inline void add(int &x,int y){
 x+=y;
 if(x>=mod) x-=mod;
}

inline void Dijkstra(){
 dist[0][0]=arr[0][0]+arr[n-1][n-1];
 dp[0][0]=1;
 pq.push(mp(-dist[0][0],mp(0,0)));
 while(!pq.empty()){
  int cost=-pq.top().fi,r=pq.top().se.fi,c=pq.top().se.se;
  pq.pop();
  if(cost>dist[r][c] || r+c==n-1) continue;
  for(int i=0;i<4;i++){
   int nr=r+dr[i],nc=c+dc[i];
   if(0<=nr && nr<n && 0<=nc && nc<n){
    int ncost=cost+arr[nr][nc]+arr[n-1-nc][n-1-nr];
    if(ncost==dist[nr][nc])
     add(dp[nr][nc],dp[r][c]);
    else if(ncost<dist[nr][nc])
     dist[nr][nc]=ncost,dp[nr][nc]=dp[r][c],pq.push(mp(-ncost,mp(nr,nc)));
   }
  }
 }
}

int main(){
 ios_base::sync_with_stdio(0);
 cin>>n;
 while(n){
  for(int i=0;i<n;i++)
   for(int j=0;j<n;j++)
    cin>>arr[i][j],dist[i][j]=INF;
  Dijkstra();
  int best=INF,ans=0;
  for(int r=0,c=n-1;r<n;r++,c--){
   dist[r][c]-=arr[r][c];
   if(dist[r][c]<best)
    best=dist[r][c],ans=dp[r][c];
   else if(dist[r][c]==best)
    add(ans,dp[r][c]);
  }
  cout<<ans<<"\n";
  cin>>n;
 }
 return 0;
}
