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

int n,m,tc;
pii Path[2][100005][2];
vector<int> adj[2][100005];
int a,b;

void dfs1(int id,int prev,int now){
 for(int i=0;i<adj[id][now].size();i++){
  int nxt=adj[id][now][i];
  if(nxt!=prev){
   dfs1(id,now,nxt);
   if(Path[id][nxt][0].fi + 1 > Path[id][now][1].fi) Path[id][now][1]=mp(Path[id][nxt][0].fi+1,nxt);
   if(Path[id][now][0].fi < Path[id][now][1].fi) swap(Path[id][now][0],Path[id][now][1]);
  }
 }
}

void dfs2(int id,int prev,int now){
 for(int i=0;i<adj[id][now].size();i++){
  int nxt=adj[id][now][i];
  if(nxt!=prev){
   for(int j=0;j<2;j++){
    int len=Path[id][now][j].fi,lol=Path[id][now][j].se;
    if(lol!=nxt){
     if(len + 1 > Path[id][nxt][1].fi) Path[id][nxt][1]=mp(len+1,now);
     if(Path[id][nxt][0].fi < Path[id][nxt][1].fi) swap(Path[id][nxt][0],Path[id][nxt][1]);
     break;
    }
   }
   dfs2(id,now,nxt);
  }
 }
}

int main(){
 SYNC;
 cin>>tc;
 for(int t=1;t<=tc;t++){
  cin>>n>>m;
  for(int i=1;i<=n;i++){
   Path[0][i][0]=Path[0][i][1]=mp(0,-1);
   adj[0][i].clear();
  }
  for(int i=1;i<=m;i++){
   Path[1][i][0]=Path[1][i][1]=mp(0,-1);
   adj[1][i].clear();
  }
  for(int i=1;i<n;i++){
   cin>>a>>b;
   adj[0][a].pb(b);
   adj[0][b].pb(a);
  }
  for(int i=1;i<m;i++){
   cin>>a>>b;
   adj[1][a].pb(b);
   adj[1][b].pb(a);
  }  
  dfs1(0,0,1);
  dfs2(0,0,1);
  dfs1(1,0,1);
  dfs2(1,0,1);  
  LL ans=(LL)n*(LL)m;
  LL tot=0;
  for(int i=1;i<=n;i++)
   tot+=(LL)Path[0][i][0].fi;
  tot*=(LL)m;
  ans+=tot; 
  tot=0;
  for(int i=1;i<=m;i++)
   tot+=(LL)Path[1][i][0].fi;
  tot*=(LL)n;
  ans+=tot;
  cout<<"Case "<<t<<": "<<ans<<"\n"; 
 }
 //puts("ganteng");
 return 0;
}

