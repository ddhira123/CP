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

struct node{
 LL tot;
 LL sum;
 LL prop;
}stree[400005];

void build(int id,int l,int r){
 if(l==r){
  stree[id].tot=100*l;
  stree[id].sum=100;
  stree[id].prop=0;
 }
 else{
  int m=(l+r)>>1,chld=id<<1;
  build(chld,l,m);
  build(chld|1,m+1,r);
  stree[id].tot=stree[chld].tot+stree[chld|1].tot;
  stree[id].sum=stree[chld].sum+stree[chld|1].sum;
  stree[id].prop=0;
 }
}

void update(int id,int l,int r,int x,int y,LL v){
 if(x<=l && r<=y){
  stree[id].prop+=v;
  stree[id].tot+=(LL)(r-l+1)*(LL)(r+l)/2LL * v;
  stree[id].sum+=(LL)(r-l+1)*v;
 }
 else{
  int m=(l+r)>>1,chld=id<<1;
  if(stree[id].prop){
   stree[chld].prop+=stree[id].prop;
   stree[chld|1].prop+=stree[id].prop;
   stree[chld].sum+=(LL)(m-l+1)*stree[id].prop;
   stree[chld|1].sum+=(LL)(r-m)*stree[id].prop;
   stree[chld].tot+=(LL)(m-l+1)*(LL)(m+l)/2LL * stree[id].prop;
   stree[chld|1].tot+=(LL)(r-m)*(LL)(r+m+1)/2LL * stree[id].prop;
   stree[id].prop=0;
  }
  if(x<=m) update(chld,l,m,x,y,v);
  if(y>m)  update(chld|1,m+1,r,x,y,v);
  stree[id].sum=stree[chld].sum+stree[chld|1].sum;
  stree[id].tot=stree[chld].tot+stree[chld|1].tot;
 }
}

LL query(int id,int l,int r,int x,int y){
 if(x<=l && r<=y){
  //printf("%d %d %d %lld %lld\n",id,l,r,stree[id].tot,stree[id].sum);
  return stree[id].tot-(LL)(x-1)*stree[id].sum;
 }
 else{
  int m=(l+r)>>1,chld=id<<1;
  if(stree[id].prop){
   stree[chld].prop+=stree[id].prop;
   stree[chld|1].prop+=stree[id].prop;
   stree[chld].sum+=(LL)(m-l+1)*stree[id].prop;
   stree[chld|1].sum+=(LL)(r-m)*stree[id].prop;
   stree[chld].tot+=(LL)(m-l+1)*(LL)(m+l)/2LL * stree[id].prop;
   stree[chld|1].tot+=(LL)(r-m)*(LL)(r+m+1)/2LL * stree[id].prop;
   stree[id].prop=0;
  }
  LL ret=0;
  if(x<=m) ret+=query(chld,l,m,x,y);
  if(y>m)  ret+=query(chld|1,m+1,r,x,y);
  stree[id].sum=stree[chld].sum+stree[chld|1].sum;
  stree[id].tot=stree[chld].tot+stree[chld|1].tot;
  return ret;
 }
}

int tc,n,q;
char x[10];
int d,e,f;

int main(){
 tc=io();
 for(int t=1;t<=tc;t++){
  n=io(),q=io();
  build(1,1,n);
  printf("Case %d:\n",t);
  while(q--){
   scanf("%s",x);
   d=io(),e=io();
   if(x[0]=='q')
    printf("%lld\n",query(1,1,n,d,e));
   else{
    f=io();
    update(1,1,n,d,e,f);
   } 
  }
 }
 //puts("ganteng");
 return 0;
}

