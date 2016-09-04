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

int row,col,Q;

LL gcd(LL a,LL b){
 return b ? gcd(b,a%b) : a;
}


struct Inner_Node{
 
 int height,key;
 int kiri,kanan;
 LL val,sub_val;
 Inner_Node *left,*right;

 Inner_Node(int idx,LL x){
  height = 0; key = idx;
  kiri = kanan = idx;
  val = sub_val = x;
  left = NULL ; right = NULL;
 }
 
};

struct AVL_Tree{

 Inner_Node *root;
 
 AVL_Tree(){
  root = NULL;
 }

 int Get_Height(Inner_Node *x){
  return x == NULL ? -1 : x -> height;
 }
 
 int Get_Left(Inner_Node *x){
  return x == NULL ? INF : x -> kiri;
 }
 
 int Get_Right(Inner_Node *x){
  return x == NULL ? -INF : x -> kanan;
 } 
 
 LL Get_Val(Inner_Node *x){
  return x == NULL ? 0LL : x -> sub_val;
 }
 
 Inner_Node *Update(Inner_Node *x){
  x -> height = 1 + max(Get_Height(x -> left), Get_Height(x -> right));
  x -> kiri = min(Get_Left(x -> left), x -> key);
  x -> kanan = max(Get_Right(x -> right), x -> key);
  x -> sub_val = gcd(x -> val, Get_Val(x -> left));
  x -> sub_val = gcd(x -> sub_val, Get_Val(x -> right));
  return x;
 }
 
 Inner_Node *RotateRight1(Inner_Node *x){
  Inner_Node *tmp = x -> left;
  x -> left = tmp -> right;
  tmp -> right = x;
  x = Update(x);
  tmp = Update(tmp);
  return tmp;
 }
 
 Inner_Node *RotateLeft1(Inner_Node *x){
  Inner_Node *tmp = x -> right;
  x -> right = tmp -> left;
  tmp -> left = x;
  x = Update(x);
  tmp = Update(tmp);
  return tmp;
 } 
 
 Inner_Node *RotateRight2(Inner_Node *x){
  x -> left = RotateLeft1(x -> left);
  x = RotateRight1(x);
  return x;
 }
 
 Inner_Node *RotateLeft2(Inner_Node *x){
  x -> right = RotateRight1(x -> right);
  x = RotateLeft1(x);
  return x;
 } 
 
 Inner_Node *Rebalance(Inner_Node *x){
  if(x == NULL) return x;
  
  Inner_Node *L = x -> left, *R = x -> right;
  
  if(Get_Height(L) - Get_Height(R) == 2){
  
   if(Get_Height(L -> left) > Get_Height(L -> right))
    x = RotateRight1(x);
   else
    x = RotateRight2(x); 
    
  }
  else if(Get_Height(R) - Get_Height(L) == 2){
  
   if(Get_Height(R -> right) > Get_Height(R -> left))
    x = RotateLeft1(x);
   else
    x = RotateLeft2(x); 
    
  }
  return x;
 }
 
 void Insert(int nkey,LL value){
  root = Insert(root,nkey,value);
 }
 
 Inner_Node *Insert(Inner_Node *x,int nkey,LL value){
  if(x == NULL){
   x = new Inner_Node(nkey,value);
   return x;
  }
  
  if(x -> key < nkey)
   x -> right = Insert(x -> right, nkey, value);
  else if(x -> key > nkey)
   x -> left =  Insert(x -> left, nkey, value);
  else{
   x -> val = value;
  }  
  
  x = Update(x);
  
  x = Rebalance(x);
  return x;
 }
 
 LL Query(int qleft,int qright){
  return Query(root,qleft,qright);
 }
 
 LL Query(Inner_Node *x,int qleft,int qright){
  LL ret;
  if(x == NULL) ret = 0;
  else if(x -> kanan < qleft || x -> kiri > qright) ret = 0;
  else if(qleft <= x -> kiri && x -> kanan <= qright) ret = x -> sub_val;
  else{
   ret = 0;
   if(x -> key >= qleft && x -> key <= qright) ret = x -> val;
   ret = gcd(ret,Query(x -> left,qleft,qright));
   ret = gcd(ret,Query(x -> right,qleft,qright));
   //return ret;
  }
  //if(x!=NULL)
   //printf("%d %d %d %d %lld\n",x -> kiri, x -> kanan,qleft,qright,ret);
  return ret;
 }
 
};

struct Outer_Node{
 
 AVL_Tree Inside;
 Outer_Node *left, *right;
 
 Outer_Node(int idx,LL x){
  Inside.Insert(idx,x);
  left = NULL ; right = NULL;
 }
 
 void Insert(int idx,LL x){
  Inside.Insert(idx,x);
 }
 
 LL Query(int qleft,int qright){
  return Inside.Query(qleft,qright);
 }
};

struct Segment_Tree{
 
 Outer_Node *root;
 
 Segment_Tree(){
  root = new Outer_Node(0,0);
 }
 
 void Insert(int rkey,int ckey,LL value){
  Insert(root,0,row-1,rkey,ckey,value);
 }
 
 void Insert(Outer_Node *x,int l,int r,int rkey,int ckey,LL value){
  if(l == r)
   x -> Insert(ckey,value);
  else{
   int m = (l+r)>>1;
   
   if(rkey <= m){
    if(x -> left == NULL) x -> left = new Outer_Node(ckey,value);
    Insert(x -> left,l,m,rkey,ckey,value);
   }
   else{
    if(x -> right == NULL) x -> right = new Outer_Node(ckey,value);
    Insert(x -> right,m+1,r,rkey,ckey,value);
   }
      
   LL ret = 0;
   if(x -> left != NULL) ret = gcd(ret,x -> left -> Query(ckey,ckey));
   if(x -> right != NULL) ret = gcd(ret,x -> right -> Query(ckey,ckey));
   x -> Insert(ckey,ret);
   
   //printf("%d %d %d %d %lld\n",l,r,rkey,ckey,ret);
  } 
 }
 
 LL Query(int ra,int ca,int rb,int cb){
  return Query(root,0,row-1,ra,rb,ca,cb);
 }
 
 LL Query(Outer_Node *x,int l,int r,int ra,int rb,int ca,int cb){
  LL ret = 0;
  if(ra <= l && r <= rb)
   ret = x -> Query(ca,cb);
  else{
   int m = (l+r) >>1;
   if(ra <= m && x -> left != NULL) ret = gcd(ret,Query(x -> left,l,m,ra,rb,ca,cb));
   if(rb > m && x-> right != NULL)  ret = gcd(ret,Query(x -> right,m+1,r,ra,rb,ca,cb));
  } 
  //printf("%d %d %d %d %d %d %lld\n",l,r,ra,rb,ca,cb,ret);
  return ret;
 }
};

int main(){
 Segment_Tree D2Tree;
 scanf("%d %d %d",&row,&col,&Q);
 while(Q--){
  int a,b,c,d,op;
  LL x;
  scanf("%d",&op);
  if(op == 1){
   scanf("%d %d %lld",&a,&b,&x);
   D2Tree.Insert(a,b,x);
  }
  else{
   scanf("%d %d %d %d",&a,&b,&c,&d);
   printf("%lld\n",D2Tree.Query(a,b,c,d));
  }
 }
 //puts("ganteng");
 return 0;
}

