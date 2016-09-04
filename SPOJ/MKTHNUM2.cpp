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

const int MAXN = 100005;
const int MAXSZ = 2000005;

struct node{
 int L,R;
 int sum;
 
 node(){
  sum = 0;
 }
};

node stree[MAXSZ];
int root[MAXN];
int compress[MAXN], arr[MAXN];
int cnt;
int n,q,len;

void Build(int id,int l,int r){
 if(l < r){
  int m = (l + r) >> 1;
  stree[id].L = ++cnt;
  stree[id].R = ++cnt;
  Build(stree[id].L,l,m);
  Build(stree[id].R,m+1,r);
 }
}

void Update(int now,int prev,int l,int r,int x){
 if(l == r)
  stree[now].sum = stree[prev].sum + 1;
 else{
  int m = (l + r) >> 1;
  if(x <= m){
   stree[now].R = stree[prev].R;
   stree[now].L = ++cnt;
   Update(stree[now].L,stree[prev].L,l,m,x);
  }
  else{
   stree[now].L = stree[prev].L;
   stree[now].R = ++cnt;
   Update(stree[now].R,stree[prev].R,m+1,r,x);
  }
  stree[now].sum = stree[stree[now].L].sum + stree[stree[now].R].sum;
 } 
}

int GetKth(int lo,int hi,int k){
 lo--;
 int l = 0, r = len;
 int tot = 0;
 int x = root[lo], y = root[hi];
 while(l < r){
  int m = (l + r) >> 1;
  if(tot + stree[stree[y].L].sum - stree[stree[x].L].sum >= k){
   r = m;
   y = stree[y].L;
   x = stree[x].L;
  }
  else{
   l = m + 1;
   tot += stree[stree[y].L].sum - stree[stree[x].L].sum;
   y = stree[y].R;
   x = stree[x].R;
  }
 }
 return l;
}

void Make_Unique(){
 sort(compress,compress + n);
 len = unique(compress,compress + n) - compress;
 len--;
}

int ID(int x){
 int lo = 0, hi = len;
 while(lo < hi){
  int mi = (lo + hi) >> 1;
  if(compress[mi] >= x) hi = mi;
  else lo = mi + 1;
 }
 return lo;
}

int main(){
 scanf("%d %d",&n,&q);
 for(int i = 0 ; i < n ; i++)
  scanf("%d",&arr[i]), compress[i] = arr[i];
 Make_Unique();
 
 Build(0,0,len);
 for(int i = 0 ; i < n ; i++){
  root[i+1] = ++cnt;
  Update(root[i+1],root[i],0,len,ID(arr[i]));
 } 
 //printf("%d\n",cnt);
 
 while(q--){
  int a,b,k;
  scanf("%d %d %d",&a,&b,&k);
  printf("%d\n",compress[GetKth(a,b,k)]);
 }
 //puts("ganteng");
 return 0;
}

