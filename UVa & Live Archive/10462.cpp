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
typedef unsigned long long ULL;
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

vector<pii> adj[105];
pair<int,pii> arr[205];
int n,m,tc;
bool use[205];
int par[105];
int path[105][105];
 
int finds(int x){
 return (x==par[x]) ? x : par[x]=finds(par[x]);
} 

void dfs(int from,int now,int prev,int maks){
 path[from][now]=maks;
 for(int i=0;i<adj[now].size();i++){
  int nxt=adj[now][i].fi,cost=adj[now][i].se;
  if(nxt!=prev)
   dfs(from,nxt,now,max(maks,cost));
 }
}

int main(){
 scanf("%d",&tc);
 for(int t=1;t<=tc;t++){
  scanf("%d %d",&n,&m);
  for(int i=1;i<=n;i++)
   adj[i].clear(),par[i]=i;
  for(int i=0;i<m;i++)
   scanf("%d %d %d",&arr[i].se.fi,&arr[i].se.se,&arr[i].fi),use[i]=0;
  sort(arr,arr+m);
  int tot=n-1;
  int mst=0;
  for(int i=0;i<m && tot>0;i++){
   int a=arr[i].se.fi,b=arr[i].se.se,cost=arr[i].fi;
   if(finds(a)!=finds(b)){
    par[finds(b)]=finds(a);
    adj[b].pb(mp(a,cost));
    adj[a].pb(mp(b,cost));
    mst+=cost;
    use[i]=1;
    tot--;
   }
  }
  printf("Case #%d : ",t);
  if(tot!=0) puts("No way");
  else if(m==n-1) puts("No second way");
  else{
   for(int i=1;i<=n;i++)
    dfs(i,i,-1,0);
   int mini=INF;
   for(int i=0;i<m;i++)
    if(!use[i]){
     int a=arr[i].se.fi,b=arr[i].se.se,cost=arr[i].fi;
     mini=min(mini,cost-path[a][b]);
    }
   printf("%d\n",mst+mini); 
  } 
 }
 //puts("ganteng");
 return 0;
}

