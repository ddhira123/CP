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

struct Node{
 int sum;
 Node *L, *R;
 
 Node(){
  sum = 0;
  L = R = NULL;
 }
};

Node *root[MAXN];
int arr[MAXN], compress[MAXN];
int n,q,len;

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

void Build(Node *x,int l,int r){
 if(l < r){
  int m = (l + r) >> 1;
  x -> L = new Node();
  x -> R = new Node();
  Build(x -> L, l, m);
  Build(x -> R, m + 1, r);
 }
}

void Update(Node *now,Node* prev,int l,int r,int x){
 if(l == r){
  now -> sum = prev -> sum + 1;
 }
 else{
  int m = (l + r) >> 1;
  if(x <= m){
   now -> R = prev -> R;
   now -> L = new Node();
   Update(now -> L, prev -> L, l, m, x);
  }
  else{
   now -> L = prev -> L;
   now -> R = new Node();
   Update(now -> R, prev -> R, m + 1 , r, x);
  }
  now -> sum = now -> L -> sum + now -> R -> sum;
 }
}

void Print(Node *now,int l,int r){
 printf("%d %d SUM %d\n",l,r,now -> sum);
 if(l < r){
  int m = (l + r) >> 1;
  Print(now -> L, l, m);
  Print(now -> R, m+1, r);
 }
}

int GetKth(int lo,int hi,int k){
 lo--;
 int tot = 0;
 int l = 0, r = len;
 /*printf("CHECK %d\n",lo);
 Print(root[lo],0,len);
 printf("CHECK %d\n",hi);
 Print(root[hi],0,len);*/
 Node *x = root[lo], *y = root[hi];
 while(l < r){
  int m = (l + r) >> 1;
  //printf("check %d %d TOT -> %d\n",l,r,tot + y -> L -> sum - x -> L -> sum);
  if(tot + y -> L -> sum - x -> L -> sum >= k){
   r = m;
   y = y -> L;
   x = x -> L;
  }
  else{
   tot += y -> L -> sum - x -> L -> sum;
   l = m + 1;
   y = y -> R;
   x = x -> R;
  }
  //printf("%d %d %d\n",l,r,tot);
 }
 return l;
}

int main(){
 scanf("%d %d",&n,&q);
 for(int i = 0 ; i < n ; i++)
  scanf("%d", &arr[i]), compress[i] = arr[i];
 Make_Unique();
 
 root[0] = new Node();
 Build(root[0],0,len);
 for(int i = 0 ; i < n ; i++){
  root[i+1] = new Node();
  Update(root[i+1],root[i],0,len,ID(arr[i]));
 }
 
 while(q--){
  int a,b,k;
  scanf("%d %d %d",&a,&b,&k);
  printf("%d\n",compress[GetKth(a,b,k)]);
 } 
 //puts("ganteng");
 return 0;
}
