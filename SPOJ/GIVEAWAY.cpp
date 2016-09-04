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
 int val;
 int sz;
 int hi;
 int jum;
 node *l,*r;
 node(int x){
  val=x;
  sz=1;
  hi=0;
  jum=1;
  l=r=NULL;
 }
};

struct AVL{
 node *root;
 
 AVL(){
  root=NULL;
 }
 
 inline int size(node *x){
  return x==NULL ? 0 : x->sz;
 }
 
 inline int height(node *x){
  return x==NULL ? -1 : x->hi;
 }
 
 inline node *update(node *x){
  if(x==NULL) return x;
  x->sz=x->jum+size(x->l)+size(x->r);
  x->hi=1+max(height(x->l),height(x->r));
  return x;
 }
 
 inline node *rotateright1(node *x){
  node *tmp=x->l;
  x->l=tmp->r;
  tmp->r=x;
  x=update(x);
  tmp=update(tmp);
  return tmp;
 }
 
 inline node *rotateleft1(node *x){
  node *tmp=x->r;
  x->r=tmp->l;
  tmp->l=x;
  x=update(x);
  tmp=update(tmp);
  return tmp;
 } 
 
 inline node *rotateright2(node *x){
  x->l=rotateleft1(x->l);
  x=rotateright1(x);
  x=update(x);
  return x;
 }
 
 inline node *rotateleft2(node *x){
  x->r=rotateright1(x->r);
  x=rotateleft1(x);
  x=update(x);
  return x;
 } 
 
 inline node *rebalance(node *x){
  if(x==NULL) return x;
  node *L=x->l,*R=x->r;
  if(height(L)-height(R)==2){
   if(height(L->l) > height(L->r))
    x=rotateright1(x);
   else
    x=rotateright2(x); 
  }
  else if(height(R)-height(L)==2){
   if(height(R->r) > height(R->l))
    x=rotateleft1(x);
   else 
    x=rotateleft2(x); 
  }
  x=update(x);
  return x; 
 }
 
 inline void insert(int v){
  root=insert(root,v);
 }
 
 node *insert(node *x,int v){
  if(x==NULL){
   x=new node(v);
   return x;
  }
  if(x->val < v)
   x->r=insert(x->r,v);
  else if(x->val > v)
   x->l=insert(x->l,v);
  else
   x->sz++,x->jum++;
  x=update(x);
  x=rebalance(x);
  return x;   
 }
 
 inline node *getmin(node *x){
  while(x->l!=NULL) x=x->l;
  return x;
 }
 
 node *displacemin(node *x){
  if(x->l==NULL) return x->r;
  x->l=displacemin(x->l);
  x=update(x);
  x=rebalance(x);
  return x;
 }
 
 inline void remove(int x){
  root=remove(root,x);
 }
 
 node *remove(node *x,int v){
  if(x==NULL) return x;
  if(x->val < v)
   x->r=remove(x->r,v);
  else if(x->val > v)
   x->l=remove(x->l,v);
  else{
   x->sz--;
   x->jum--;
   if(x->jum==0){
    if(x->l==NULL && x->r==NULL)
     x=NULL;
    else if(x->l!=NULL && x->r!=NULL){
     node *tmp=getmin(x->r);
     x->r=displacemin(x->r);
     tmp->l=x->l;
     tmp->r=x->r;
     x=tmp;
     tmp=NULL;
    } 
    else
     x= (x->l==NULL ? x->r : x->l);
   }
  }
  x=update(x);
  x=rebalance(x);
  return x;  
 }
 
 inline int query(int v){
  return query(root,v);
 }
 
 inline int query(node *x,int v){
  int ret=0;
  while(x!=NULL){
   if(x->val < v)
    x=x->r;
   else
    ret+=size(x)-size(x->l),x=x->l; 
  }
  return ret;
 }
};

AVL BIT[500005];
int n,q,a,b,c,d;
int arr[500005];

inline void B_Update(int x,int v,int op){
 if(op)
  for(;x<=n;x+=x&-x)
   BIT[x].remove(v);
 else
  for(;x<=n;x+=x&-x)
   BIT[x].insert(v);  
}

inline int B_Query(int x,int v){
 int ret=0;
 for(;x;x-=x&-x)
  ret+=BIT[x].query(v);
 return ret; 
}

int main(){
  n=io();
  for(int i=1;i<=n;i++)
   arr[i]=io(),B_Update(i,arr[i],0); 
  q=io();
  while(q--){
   a=io(),b=io(),c=io();
   if(a){
    //DEBUG;
    B_Update(b,arr[b],1);
    //DEBUG;
    arr[b]=c;
    B_Update(b,arr[b],0);
    //DEBUG;
   }
  else{
   d=io();
   printf("%d\n",B_Query(c,d)-B_Query(b-1,d));
  } 
  } 
 //puts("ganteng");
 return 0;
}

