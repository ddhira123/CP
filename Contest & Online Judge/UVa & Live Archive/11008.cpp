#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <bitset>
#include <cassert>
#define makmu using
#define ndasmu namespace
#define gundulmu std

makmu ndasmu gundulmu;

typedef long long LL;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;
typedef pair<string,string> pss;
typedef pair<int,double> pid;
typedef pair<int,LL> pil;
typedef pair<LL,LL> pll;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SYNC ios_base::sync_with_stdio(false)
#define TIE cin.tie(0)
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL
#define DEBUG puts("DEBUG")

#ifdef _WIN32
#define getchar_unlocked getchar
#endif

#define g getchar_unlocked

int dx8[8]={-1,-1,0,1,1,1,0,-1},dx4[4]={-1,0,1,0};
int dy8[8]={0,-1,-1,-1,0,1,1,1},dy4[4]={0,-1,0,1};

inline void open(string name){
 freopen((name+".in").c_str(),"r",stdin);
 freopen((name+".out").c_str(),"w",stdout);
}

inline void close(){
 fclose(stdin);
 fclose(stdout);
}

inline int io(){
 register char c;
 while(1){
  c=g();
  if(c!='\n' && c!=' ') break;
 }
 int res=0,sign=1;
 if(c=='-') sign=-1;
 else       res=c-'0';
 while(1){
  c=g();
  if(c==' ' || c=='\n' || c==EOF) break;
  res=(res<<3)+(res<<1)+c-'0';
 }
 return res*sign;
}

///////////////////////////////////////////////////
//////            End of Template            /////
/////////////////////////////////////////////////

struct point{
 int x,y;
}arr[20];

int dp[(1<<16)+5];
int n,tc,m;
vector<int> adj[20];

int Cross(int x1,int y1,int x2,int y2){
 return x1*y2 - x2*y1;
}

bool Collinear(point a,point b,point c){
 return Cross(a.x-b.x,a.y-b.y,a.x-c.x,a.y-c.y)==0;
}

int main(){
 scanf("%d",&tc);
 for(int t=1;t<=tc;t++){
  scanf("%d %d",&n,&m);
  for(int i=(1<<n)-1;i>=0;i--) dp[i]=INF;
  dp[0]=0;
  for(int i=0;i<n;i++)
   adj[i].clear(),adj[i].pb(1<<i),scanf("%d %d",&arr[i].x,&arr[i].y);
  for(int i=0;i<n;i++)
   for(int j=i+1;j<n;j++){
    int mask=0;
    for(int k=0;k<n;k++)
     if(Collinear(arr[i],arr[j],arr[k]))
      mask|=(1<<k);
    for(int k=0;k<n;k++)
     if(mask&(1<<k))
      adj[k].pb(mask);  
   }
  int ans=INF; 
  for(int i=0;i<(1<<n);i++){
   if(__builtin_popcount(i)>=m)
    ans=min(ans,dp[i]);
   else
    for(int j=0;j<n;j++)
     if((i&(1<<j))==0){
      for(int k=0;k<adj[j].size();k++){
       int nxt=adj[j][k];
       dp[i|nxt]=min(dp[i]+1,dp[i|nxt]);
      }
     } 
  }
  printf("Case #%d:\n%d\n",t,ans);
  if(t<tc) puts("");  
 }
 //puts("ganteng");
 return 0;
}

