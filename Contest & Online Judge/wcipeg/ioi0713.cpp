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

struct Node{
 int kiri;
 int kanan;
 
 Node(){
  kiri = kanan = 0;
 }
};

Node Stree[400010];
int n;
int maxh;
pii arr[100005];

void Update(int id,int l,int r,int x,int val){
 if(l == r){
  Stree[id].kiri += val;
  Stree[id].kanan += val;
 }
 else{
  int m = (l + r)/2, chld = id*2;
  if(x <= m) Update(chld,l,m,x,val);
  else       Update(chld+1,m+1,r,x,val);
  Stree[id].kiri = Stree[chld].kiri;
  Stree[id].kanan = Stree[chld].kanan + Stree[chld+1].kanan;
 }
}

int Query(int id,int l,int r,int x,int y){
 if(x <= l && r <= y)
  return Stree[id].kanan;
 else{
  int ret = 0;
  int m = (l + r)/2, chld = id*2;
  if(x <= m) ret += Query(chld,l,m,x,y);
  if(y  > m) ret += Query(chld+1,m+1,r,x,y);
  return ret;
 } 
}

int LeftMost(int val){
 int add = 0;
 int id = 1;
 int l = 1,r = maxh;
 while(l < r){
  int chld = id*2;
  int m = (l + r)/2;
  if(add + Stree[chld].kanan <= val)
   id = chld,r = m;
  else
   add += Stree[chld].kanan, id = chld + 1, l = m+1; 
 }
 return l;
}

int RightMost(int val){
 int add = 0;
 int id = 1;
 int l = 1,r = maxh;
 while(l < r){
  int chld = id*2;
  int m = (l + r)/2;
  if(add + Stree[chld].kanan + Stree[chld+1].kiri >= val)
   add += Stree[chld].kanan, id = chld + 1, l = m+1;
  else
   id = chld, r = m; 
 }
 return l;
}

int main(){
 scanf("%d",&n);
 for(int i = 0 ; i < n ; i++)
  scanf("%d %d",&arr[i].fi,&arr[i].se);
 sort(arr,arr+n);
 maxh = arr[n-1].fi + 1;
 for(int i = 0 ; i < n ; i++){
  int h = arr[i].fi;
  int kiri = h - arr[i].se + 1;
  int val = Query(1,1,maxh,1,kiri);
  
  int limit_kiri = LeftMost(val);
  int limit_kanan = RightMost(val);
  limit_kanan = min(limit_kanan,h);
  
  int jum = arr[i].se - (h - limit_kanan);
  Update(1,1,maxh,limit_kiri,1);
  Update(1,1,maxh,limit_kiri + jum,-1);
  Update(1,1,maxh,limit_kanan + 1,1);
  Update(1,1,maxh,h + 1,-1);
 } 
 LL ans = 0;
 for(int i = 1 ; i < maxh ; i++){
  LL tmp = Query(1,1,maxh,1,i);
  ans += tmp*(tmp-1)/2LL;
 }
 printf("%lld\n",ans);
 //puts("ganteng");
 return 0;
}

