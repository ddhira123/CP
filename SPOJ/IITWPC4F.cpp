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

const int MAXX = 100000;

struct node{
 int sum;
 bool rev;

 node(){
  sum = 0;
  rev = 0;
 }
};

int q;
char s[5];
int a,b,c,d;
node stree[2][4*MAXX + 5];

void Propagate(int dim,int id,int l,int r){
 if(!stree[dim][id].rev) return;
 stree[dim][id].rev = 0;
 int chld = id << 1, m = (l + r) >> 1;

 stree[dim][chld].rev ^= 1;
 stree[dim][chld+1].rev ^= 1;

 stree[dim][chld].sum = m-l+1 - stree[dim][chld].sum;
 stree[dim][chld+1].sum = r-m - stree[dim][chld+1].sum;
}

void Update(int dim,int id,int l,int r,int x,int y){
 if(x <= l && r <= y){
  stree[dim][id].rev ^= 1;
  stree[dim][id].sum = r-l+1 - stree[dim][id].sum;
 }
 else{
  int chld = id << 1, m = (l + r) >> 1;
  Propagate(dim,id,l,r);
  if(x <= m) Update(dim,chld,l,m,x,y);
  if(y > m) Update(dim,chld+1,m+1,r,x,y);
  stree[dim][id].sum = stree[dim][chld].sum + stree[dim][chld+1].sum;
 }
}

int Query(int dim,int id,int l,int r,int x,int y){
 if(x <= l && r <= y){
  return stree[dim][id].sum;
 }
 else{
  int chld = id << 1, m = (l + r) >> 1;
  int ret = 0;
  Propagate(dim,id,l,r);
  if(x <= m) ret += Query(dim,chld,l,m,x,y);
  if(y > m)  ret += Query(dim,chld+1,m+1,r,x,y);
  return ret;
 }
}

int main(){
 scanf("%d",&q);
 while(q--){
  scanf("%s %d %d",s,&a,&b);
  if(s[0] == 'q'){
   scanf("%d %d",&c,&d);
   if(a > c) swap(a,c);
   if(b > d) swap(b,d);
   LL X = Query(0,1,0,MAXX,a,c);
   LL Y = Query(1,1,0,MAXX,b,d);
   LL ans = (X)*(LL)(d-b+1 - Y) + (Y)*(LL)(c-a+1 - X);
   printf("%lld\n",ans);
  }
  else
   Update(s[0]-'x',1,0,MAXX,a,b);
 }
 return 0;
}
