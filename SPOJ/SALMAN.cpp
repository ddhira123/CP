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
#define N 100005

struct node{
 LL Sum;
 LL Min;
 LL Lazy;
};

int id[N],next[N],tmp[N],arr[N];
vector<int> adj[N];
node Stree[N<<2];
int n,q,a,b,tc;
int ctr;

void DFS(int x){
 id[x]=++ctr;
 arr[ctr]=tmp[x];
 for(int i=0;i<adj[x].size();i++)
  DFS(adj[x][i]);
 next[x]=ctr;
}

void Build(int idx,int l,int r){
 if(l==r)
  Stree[idx].Sum=Stree[idx].Min=arr[l],Stree[idx].Lazy=0;
 else{
  int m=(l+r)>>1,chld=idx<<1;
  Build(chld,l,m);
  Build(chld|1,m+1,r);
  Stree[idx].Sum=Stree[chld].Sum+Stree[chld|1].Sum;
  Stree[idx].Min=min(Stree[chld].Min,Stree[chld|1].Min);
  Stree[idx].Lazy=0;
 } 
}

void Update(int idx,int l,int r,int x,int y,LL val){
 if(x<=l && r<=y){
  Stree[idx].Min+=val;
  Stree[idx].Lazy+=val;
  Stree[idx].Sum+=val*(LL)(r-l+1);
 }
 else{
  int m=(l+r)>>1,chld=idx<<1;
  if(Stree[idx].Lazy){
   Stree[chld].Min+=Stree[idx].Lazy;
   Stree[chld|1].Min+=Stree[idx].Lazy;
   Stree[chld].Lazy+=Stree[idx].Lazy;
   Stree[chld|1].Lazy+=Stree[idx].Lazy;
   Stree[chld].Sum+=(m-l+1)*Stree[idx].Lazy;
   Stree[chld|1].Sum+=(r-m)*Stree[idx].Lazy;
  }
  if(x<=m) Update(chld,l,m,x,y,val);
  if(y>m)  Update(chld|1,m+1,r,x,y,val);
  Stree[idx].Sum=Stree[chld].Sum+Stree[chld|1].Sum;
  Stree[idx].Min=min(Stree[chld].Min,Stree[chld|1].Min);
  Stree[idx].Lazy=0;  
 }
}

LL Query_Min(int idx,int l,int r,int x,int y){
 if(x<=l && r<=y){
  return Stree[idx].Min;
 }
 else{
  int m=(l+r)>>1,chld=idx<<1;
  if(Stree[idx].Lazy){
   Stree[chld].Min+=Stree[idx].Lazy;
   Stree[chld|1].Min+=Stree[idx].Lazy;
   Stree[chld].Lazy+=Stree[idx].Lazy;
   Stree[chld|1].Lazy+=Stree[idx].Lazy;
   Stree[chld].Sum+=(m-l+1)*Stree[idx].Lazy;
   Stree[chld|1].Sum+=(r-m)*Stree[idx].Lazy;
  }
  LL ret=INFLL;
  if(x<=m) ret=min(ret,Query_Min(chld,l,m,x,y));
  if(y>m)  ret=min(ret,Query_Min(chld|1,m+1,r,x,y));
  Stree[idx].Sum=Stree[chld].Sum+Stree[chld|1].Sum;
  Stree[idx].Min=min(Stree[chld].Min,Stree[chld|1].Min);
  Stree[idx].Lazy=0;  
  return ret;
 }
}

LL Query_Sum(int idx,int l,int r,int x,int y){
 if(x<=l && r<=y){
  return Stree[idx].Sum;
 }
 else{
  int m=(l+r)>>1,chld=idx<<1;
  if(Stree[idx].Lazy){
   Stree[chld].Min+=Stree[idx].Lazy;
   Stree[chld|1].Min+=Stree[idx].Lazy;
   Stree[chld].Lazy+=Stree[idx].Lazy;
   Stree[chld|1].Lazy+=Stree[idx].Lazy;
   Stree[chld].Sum+=(m-l+1)*Stree[idx].Lazy;
   Stree[chld|1].Sum+=(r-m)*Stree[idx].Lazy;
  }
  LL ret=0;
  if(x<=m) ret+=Query_Sum(chld,l,m,x,y);
  if(y>m)  ret+=Query_Sum(chld|1,m+1,r,x,y);
  Stree[idx].Sum=Stree[chld].Sum+Stree[chld|1].Sum;
  Stree[idx].Min=min(Stree[chld].Min,Stree[chld|1].Min);
  Stree[idx].Lazy=0;  
  //printf("%d %d %d %d %lld\n",l,r,x,y,ret);
  return ret;
 }
}


int main(){
 tc=io();
 for(int t=1;t<=tc;t++){
  n=io(),q=io();
  for(int i=0;i<=n;i++)
   adj[i].clear();
  for(int i=1;i<=n;i++){
   a=io(),tmp[i]=io();
   adj[a].pb(i);
  } 
  ctr=-1;
  DFS(0);
  Build(1,1,n);
  printf("Case %d:\n",t);
  while(q--){
   a=io(),b=io();
   if(a==1)
    printf("%lld\n",Query_Sum(1,1,n,id[b],next[b]));
   else{
    LL ret=Query_Min(1,1,n,id[b],next[b]);
    ret=min(ret,1000LL);
    Update(1,1,n,id[b],next[b],ret);
   } 
  }
 }
 //puts("ganteng");
 return 0;
}

