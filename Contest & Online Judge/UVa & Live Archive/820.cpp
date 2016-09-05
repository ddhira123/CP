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

int a,b,c,n,s,t,tc,x;
int res[105][105];
vector<int> adj[105];
queue<int> q;
int par[105],lvl[105],f,mf;

inline void reset(){
 for(int i=1;i<=n;i++){
  adj[i].clear();
  for(int j=1;j<=n;j++)
   res[i][j]=0;
 }
}

void Augment(int pos,int cost){
 if(cost==0) return;
 if(pos==s){
  f=cost;
  return;
 }
 Augment(par[pos],min(cost,res[par[pos]][pos]));
 res[par[pos]][pos]-=f;
 res[pos][par[pos]]+=f;
}

inline void PlayBFS(){
 while(!q.empty()) q.pop();
 for(int i=1;i<=n;i++)
  par[i]=lvl[i]=-1;
 par[s]=lvl[s]=0;
 q.push(s);
 while(!q.empty()){
  int pos=q.front(); q.pop();
  if(pos==t) break;
  for(int i=0;i<adj[pos].size();i++){
   int nxt=adj[pos][i];
   if(lvl[nxt]==-1 && res[pos][nxt])
    lvl[nxt]=lvl[pos]+1,par[nxt]=pos,q.push(nxt);
  }
 }  
}

inline void PlayDinic(){
 mf=0;
 while(1){
  PlayBFS();
  if(par[t]==-1) break;
  for(int i=0;i<adj[t].size();i++){
   int prev=adj[t][i];
   if(lvl[prev]+1!=lvl[t] || res[prev][t]==0) continue;
   f=0;
   Augment(prev,res[prev][t]);
   res[prev][t]-=f;
   res[t][prev]+=f;
   mf+=f;
  }
 }
}

int main(){
 n=io();
 while(n){
  reset();
  s=io();t=io();x=io();
  while(x--){
   a=io(),b=io(),c=io();
   res[a][b]+=c;
   res[b][a]+=c;
   adj[a].pb(b);
   adj[b].pb(a);
  }
  PlayDinic();
  printf("Network %d\nThe bandwidth is %d.\n\n",++tc,mf);
  n=io();
 }
 //puts("ganteng");
 return 0;
}

