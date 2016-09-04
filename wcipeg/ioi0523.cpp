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
#define INF 2100000000
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

int dist[105][105];
int n,k;
int wood[105];
vector<pii> adj[105];
int dp[105][105][55];
int left_child[105],right_child[105];
vector<int> adj2[105];

void DFS(int start,int now,int prev,int tot){
 dist[start][now]=tot;
 for(int i=0;i<adj[now].size();i++){
  pii lol=adj[now][i];
  if(lol.fi!=prev)
   DFS(start,lol.fi,now,tot+lol.se);
 }
}

void LCRS(){
 memset(left_child,-1,sizeof left_child);
 memset(right_child,-1,sizeof right_child);
 for(int i=0;i<=n;i++){
  //printf("%d\n",i);
  if(!adj2[i].empty())
   left_child[i]=adj2[i][0];
  //printf("%d %d\n",i,adj2[i].size()); 
  for(int j=0;j+1<adj2[i].size();j++){
   int idx=adj2[i][j];
   int idx2=adj2[i][j+1];
   right_child[idx]=idx2;
  } 
 }
}

int solve(int prev,int now,int left){
 //printf("%d %d %d\n",prev,now,left);
 //g();
 //if(now==-1) return 0;
 if(dp[prev][now][left]!=-1)
  return dp[prev][now][left];
 int ret1=INF,ret2=INF;
 if(right_child[now]!=-1 && left_child[now]!=-1)
 for(int i=0;i<=left;i++)
  ret1=min(ret1,solve(prev,left_child[now],i) + solve(prev,right_child[now],left-i));
 else if(left_child[now]!=-1)
  ret1=solve(prev,left_child[now],left);
 else if(right_child[now]!=-1)
  ret1=solve(prev,right_child[now],left);
 else
  ret1=0;   
 ret1+=dist[prev][now]*wood[now];
 if(left){
 if(right_child[now]!=-1 && left_child[now]!=-1)
 for(int i=0;i<left;i++)
  ret2=min(ret2,solve(now,left_child[now],i) + solve(prev,right_child[now],left-i-1));
 else if(left_child[now]!=-1)
  ret2=solve(now,left_child[now],left-1);
 else if(right_child[now]!=-1)
  ret2=solve(prev,right_child[now],left-1);
 else
  ret2=0; 
 }
 return dp[prev][now][left]=min(ret1,ret2);  
}

int main(){
 scanf("%d %d",&n,&k);
 for(int i=1;i<=n;i++){
  int a,b,c;
  scanf("%d %d %d",&a,&b,&c);
  wood[i]=a;
  adj2[b].pb(i);
  adj[i].pb(mp(b,c));
  adj[b].pb(mp(i,c));
 }
 for(int i=0;i<=n;i++)
  DFS(i,i,-1,0);
 LCRS();
 memset(dp,-1,sizeof dp);
 //for(int i=0;i<=n;i++)
  //printf("%d %d %d\n",i,left_child[i],right_child[i]);
 printf("%d\n",solve(0,0,k)); 
 //puts("ganteng");
 return 0;
}

