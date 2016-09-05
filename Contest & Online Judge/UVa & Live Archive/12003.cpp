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

typedef pair<int,int> pii;
typedef long long LL;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SYNC ios_base::sync_with_stdio(false)
#define g getchar_unlocked
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL
#define DEBUG puts("DEBUG")
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
 int key;
 int sz,cnt;
 int hi;
 node *l,*r;
 node(int v){
  key=v;
  sz=cnt=1;
  hi=0;
  l=r=NULL;
 }
};

struct AVL{
 node *root;
 
 AVL(){
  root=NULL;
 }
 
 int height(node *x){
  return (x==NULL ? -1 : x->hi);
 }
 
 int size(node *x){
  return (x==NULL ? 0 : x->sz);
 }
 
 node *update(node *x){
  if(x==NULL) return x;
  x->hi=1 + max(height(x->l),height(x->r));
  x->sz= x->cnt + size(x->l) +size(x->r);
  return x; 
 }
 
 node *rotright1(node *x){
  node *tmp=x->l;
  x->l=tmp->r;
  tmp->r=x;
  x=update(x);
  tmp=update(tmp);
  return tmp;
 }
 
 node *rotleft1(node *x){
  node *tmp=x->r;
  x->r=tmp->l;
  tmp->l=x;
  x=update(x);
  tmp=update(tmp);
  return tmp;
 }
 
 node *rotright2(node *x){
  x->l=rotleft1(x->l);
  x=rotright1(x);
  return x;
 }
 
 node *rotleft2(node *x){
  x->r=rotright1(x->r);
  x=rotleft1(x);
  return x;
 }
 
 node *rebalance(node *x){
  if(x==NULL) return x;
  node *L=x->l,*R=x->r;
  if(height(L)-height(R)==2){
   if(height(L->l) > height(L->r))
    x=rotright1(x);
   else
    x=rotright2(x); 
  }
  else if(height(R)-height(L)==2){
   if(height(R->r) > height(R->l))
    x=rotleft1(x);
   else
    x=rotleft2(x); 
  }
  x=update(x);
  return x;
 }
 
 node *GetMin(node *x){
  while(x->l!=NULL) x=x->l;
  return x;
 }
 
 node *Displace(node *x){
  if(x->l==NULL) return x->r;
  x->l=Displace(x->l);
  x=update(x);
  x=rebalance(x);
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
  if(v < x->key)
   x->l=insert(x->l,v);
  else if(v > x->key)
   x->r=insert(x->r,v);
  else
   x->cnt++;
  x=update(x);
  x=rebalance(x);
  return x;   
 }
 
 inline void remove(int v){
  root=remove(root,v);
 }
 
 node *remove(node *x,int v){
  if(x==NULL) return x;
  //printf("NOW %d %d\n",x->key,v);
  if(v < x->key)
   x->l=remove(x->l,v);
  else if(v > x->key)
   x->r=remove(x->r,v);
  else{
   x->cnt--;
   x->sz--;
   if(x->cnt==0){
    if(x->l==NULL && x->r==NULL) x=NULL;
    else if(x->l!=NULL && x->r!=NULL){
     node *tmp=GetMin(x->r);
     x->r=Displace(x->r);
     tmp->l=x->l;
     tmp->r=x->r;
     x=tmp;
     tmp=NULL;
    }
    else
     x=(x->l==NULL ? x->r : x->l);
   }
  }
  x=update(x);
  x=rebalance(x);
  return x;  
 }
 
 inline int query(int v){
  return query(root,v);
 }
 
 int query(node *x,int v){
  if(x==NULL) return 0;
  else if(v==x->key)
   return size(x->l);
  else if(v < x->key)
   return query(x->l,v);
  else
   return size(x)-size(x->r)+query(x->r,v); 
 }
 
};

int arr[300005];
AVL BIT[300005];
int n,m,p,vv;
LL u,k,le,rig;

inline void update(int x,int v){
 for(int i=x;i<=n;i+=i&-i)
  BIT[i].insert(v);
}

inline void remove(int x,int v){
 for(int i=x;i<=n;i+=i&-i)
  BIT[i].remove(v);
}

inline int query(int x,int v){
 int ret=0;
 for(int i=x;i;i-=i&-i)
  ret+=BIT[i].query(v);
 return ret; 
}

int main(){
 n=io(),m=io(),u=io();
 for(int i=1;i<=n;i++)
  arr[i]=io(),update(i,arr[i]);
 while(m--){
  le=io(),rig=io(),vv=io(),p=io();
  k=query(rig,vv)-query(le-1,vv);
  remove(p,arr[p]);
  k=u*k/(rig-le+1LL);
  update(p,k);
  arr[p]=k;
 }
 for(int i=1;i<=n;i++)
  printf("%d\n",arr[i]); 
 //puts("ganteng");
 return 0;
}

