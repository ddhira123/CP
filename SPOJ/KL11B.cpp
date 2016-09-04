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
 int key;
 int cnt,sz;
 int hi;
 Node *l,*r;

 Node(){
  cnt = sz = 1;
  hi = 0;
  l = r = NULL;
 }
};

struct AVL{
 Node *root;

 AVL(){
  root = NULL;
 }

 int Get_Height(Node *x){return x == NULL ? -1 : x -> hi;}
 int Get_Size(Node *x){return x == NULL ? 0 : x -> sz;}

 Node *Update(Node *x){
  x -> sz = x -> cnt + Get_Size(x -> l) + Get_Size(x -> r);
  x -> hi = 1 + max(Get_Height(x -> l), Get_Height(x -> r));
  return x;
 }

 Node *RotateRight1(Node *x){
  Node *tmp = x -> l;
  x -> l = tmp -> r;
  tmp -> r = x;
  x = Update(x);
  tmp = Update(tmp);
  return tmp;
 }

 Node *RotateLeft1(Node *x){
  Node *tmp = x -> r;
  x -> r = tmp -> l;
  tmp -> l = x;
  x = Update(x);
  tmp = Update(tmp);
  return tmp;
 }

 Node *RotateRight2(Node *x){
  x -> l = RotateLeft1(x -> l);
  x = RotateRight1(x);
  return x;
 }

 Node *RotateLeft2(Node *x){
  x -> r = RotateRight1(x -> r);
  x = RotateLeft1(x);
  return x;
 }

 Node *Rebalance(Node *x){
  if(x == NULL) return x;
  Node *L = x -> l,*R = x -> r;
  if(Get_Height(L) - Get_Height(R) == 2){
    if(Get_Height(L -> l) > Get_Height(L -> r))
     x = RotateRight1(x);
    else
     x = RotateRight2(x);
  }
  else if(Get_Height(R) - Get_Height(L) == 2){
   if(Get_Height(R -> r) > Get_Height(R -> l))
    x = RotateLeft1(x);
   else
    x = RotateLeft2(x);
  }
  return x;
 }

 void Insert(int x){
  root = Insert(root,x);
 }

 Node *Insert(Node *x,int val){
  if(x == NULL){
   x = new Node();
   x -> key = val;
  }
  else if(x -> key > val)
   x -> l = Insert(x -> l,val);
  else if(x -> key < val)
   x -> r = Insert(x -> r,val);
  else
   x -> cnt++;
  x = Update(x);
  x = Rebalance(x);
  return x;
 }

 int Query(int val){
  Node *x = root;
  int ans = 0;
  while(x != NULL){
   if(x -> key >= val)
    ans += Get_Size(x) - Get_Size(x -> l), x = x -> l;
   else
    x = x -> r;
  }
  return ans;
 }
};

const int MAXN = 500005;

int compress[MAXN];
int q1[MAXN],q2[MAXN];
char op[MAXN][3];
int len;
AVL BIT[MAXN];
int n;

void BIT_Insert(int st,int val){
 for(; st <= len ; st += st&-st)
  BIT[st].Insert(val);
}

int BIT_Query(int en,int val){
 int ans = 0;
 for(; en ; en -= en&-en)
  ans += BIT[en].Query(val);
 return ans;
}

void Make_Unique(){
 sort(compress,compress + n);
 len = unique(compress,compress + n) - compress;
}

int ID(int x){
 int lo = 0, hi = len-1;
 while(lo < hi){
  int mi = (lo + hi)/2;
  if(compress[mi] < x) lo = mi+1;
  else hi = mi;
 }
 return lo+1;
}

int main(){
 scanf("%d",&n);
 for(int i = 0 ; i < n ; i++){
  scanf("%s %d %d",op[i],&q1[i],&q2[i]);
  compress[i] = q1[i];
 }
 Make_Unique();
 for(int i = 0 ; i < n ; i++){
  int id = ID(q1[i]);
  if(op[i][0] == '+')
   BIT_Insert(id,q2[i]);
  else{
   int ret = BIT_Query(id,q2[i]);
   //printf("AWAL %d ",ret);
   //ret -= BIT_Query(id - 1,q1[i]);
   printf("%d\n",ret);
  }
 }
 return 0;
}
