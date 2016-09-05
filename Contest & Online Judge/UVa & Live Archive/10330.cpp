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

int f,n,a,b,c,m;
int res[205][205];
vector<int> adj[205];
queue<int> q;
int par[205],lvl[205];

inline int in(int x){
 return x<<1;
}

inline int out(int x){
 return (x<<1)+1;
}

void Augment(int pos,int Min){
 if(Min==0) return;
 else if(pos==0){
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
 for(int i=out(n);i>=0;i--){
  adj[i].clear();
  for(int j=out(n);j>=0;j--)
   res[i][j]=0;
 }
}

inline int PlayDinic(){
 int mf=0;
 while(1){
  while(!q.empty()) q.pop();
  for(int i=out(n);i>=0;i--)
   par[i]=lvl[i]=-1;
  q.push(0);
  par[0]=lvl[0]=0;
  while(!q.empty()){
   int now=q.front(); q.pop();
   if(now==1) break;
   for(int i=0;i<adj[now].size();i++){
    int nxt=adj[now][i];
    if(par[nxt]==-1 && res[now][nxt])
     par[nxt]=now,lvl[nxt]=lvl[now]+1,q.push(nxt);
   }
  }
  if(par[1]==-1) break;
  for(int i=0;i<adj[1].size();i++){
   int prev=adj[1][i];
   if(lvl[prev]+1==lvl[1] && res[prev][1]){
    f=0;
    Augment(prev,res[prev][1]);
    res[prev][1]-=f;
    res[1][prev]+=f;
    mf+=f;
   }
  } 
 }
 return mf;
}


int main(){
 while(scanf("%d",&n)==1){
  Reset();
  for(int i=1;i<=n;i++){
   scanf("%d",&res[in(i)][out(i)]);
   adj[in(i)].pb(out(i));
   adj[out(i)].pb(in(i));
  }
  scanf("%d",&m);
  while(m--){
   scanf("%d %d %d",&a,&b,&c);
   res[out(a)][in(b)]+=c;
   adj[out(a)].pb(in(b));
   adj[in(b)].pb(out(a));
  }
  scanf("%d %d",&b,&c);
  while(b--){
   scanf("%d",&a);
   res[0][in(a)]=INF;
   adj[0].pb(in(a));
   adj[in(a)].pb(0);
  }
  while(c--){
   scanf("%d",&a);
   res[out(a)][1]=INF;
   adj[out(a)].pb(1);
   adj[1].pb(out(a));
  }
  printf("%d\n",PlayDinic());
 }
 //puts("ganteng");
 return 0;
}

