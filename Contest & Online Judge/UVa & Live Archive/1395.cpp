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

struct DSU{
 int par[105];
 
 inline void Reset(int x){
  for(int i=1; i<=x ; i++)
   par[i]=i;
 }
 
 inline int Finds(int x){
  return x==par[x] ? x : par[x]=Finds(par[x]);
 }
 
 inline bool Same(int x,int y){
  return Finds(x) == Finds(y);
 }
 
 inline void Uni(int x,int y){
  par[Finds(x)]=Finds(y);
 }
 
} lol;

pair<int,pii> arr[5005];
int n,m;

inline int Process(int x){
 lol.Reset(n);
 int Edge=n-1;
 int it=x;
 while(it < m && Edge > 0){
  int a=arr[it].se.fi,b=arr[it].se.se;
  if(!lol.Same(a,b))
   Edge--,lol.Uni(a,b);
  it++; 
 }
 if(Edge) return INF;
 else return arr[it-1].fi - arr[x].fi;
}

int main(){
 scanf("%d %d",&n,&m);
 while(n|m){
  for(int i=0;i<m;i++)
   scanf("%d %d %d",&arr[i].se.fi,&arr[i].se.se,&arr[i].fi); 
  sort(arr,arr+m);
  //for(int i=0;i<m;i++)
   //printf("%d %d %d\n",arr[i].fi,arr[i].se.fi,arr[i].se.se);
  int ans=INF;
  for(int i=0;i<m;i++){
   int haha=Process(i);
   //printf("%d %d\n",i,haha);
   if(haha==INF) break;
   else ans=min(ans,haha);
  } 
  if(ans==INF) ans=-1;
  printf("%d\n",ans);
  scanf("%d %d",&n,&m);
 }
 //puts("ganteng");
 return 0;
}

