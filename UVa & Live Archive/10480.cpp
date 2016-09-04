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

typedef pair<int,int> pii;
typedef long long LL;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SYNC ios_base::sync_with_stdio(false)
#define g getchar_unlocked
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL

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

int res[55][55];
vector<int> adj[55];
int par[55],lvl[55];
queue<int> q;
int n,a,b,c,m,f;

void Augment(int pos,int Min){
 if(Min==0) return;
 else if(pos==1){
  f=Min;
  return;
 }
 else{
  Augment(par[pos],min(Min,res[par[pos]][pos]));
  res[par[pos]][pos]-=f;
  res[pos][par[pos]]+=f;
 }
}

inline void Reset(){
 for(int i=n;i>=1;i--){
  adj[i].clear();
  for(int j=n;j>=1;j--)
   res[i][j]=0;
 }
}

inline void PlayDinic(){
 while(1){
  while(!q.empty()) q.pop();
  for(int i=n;i>=1;i--)
   par[i]=lvl[i]=-1;
  q.push(1);
  par[1]=lvl[1]=0;
  while(!q.empty()){
   int now=q.front(); q.pop();
   if(now==2) break;
   for(int i=0;i<adj[now].size();i++){
    int nxt=adj[now][i];
    if(par[nxt]==-1 && res[now][nxt])
     par[nxt]=now,lvl[nxt]=lvl[now]+1,q.push(nxt);
   }
  }
  if(par[2]==-1) break;
  for(int i=0;i<adj[2].size();i++){
   int prev=adj[2][i];
   if(lvl[prev]+1==lvl[2] && res[prev][2]){
    f=0;
    Augment(prev,res[prev][2]);
    res[prev][2]-=f;
    res[2][prev]+=f;
   }
  } 
 }
}

set<pii> S;
bool vis[55];

void dfs(int x){
 vis[x]=1;
 for(int i=0;i<adj[x].size();i++){
  int y=adj[x][i];
  if(!vis[y] && res[x][y])
   dfs(y);
 }
}

inline void Print(){
 S.clear();
 for(int i=1;i<=n;i++) vis[i]=0;
 dfs(1);
 for(int i=1;i<=n;i++)
  if(vis[i]){
   for(int j=0;j<adj[i].size();j++){
    int v=adj[i][j];
    if(vis[v]) continue;
    if(res[i][v]==0)
     S.insert(mp(min(i,v),max(i,v)));
   }
  }
 while(!S.empty()){
  pii tmp=*S.begin();
  S.erase(S.begin());
  printf("%d %d\n",tmp.fi,tmp.se);
 }
 puts(""); 
}

int main(){
 //puts("ganteng");
 n=io(); m=io();
 while(n|m){
  Reset();
  while(m--){
   a=io(),b=io(),c=io();
   adj[a].pb(b);
   adj[b].pb(a);
   res[a][b]=res[b][a]=c;
  }
  PlayDinic();
  Print();
  n=io();m=io();
 }
 return 0;
}

