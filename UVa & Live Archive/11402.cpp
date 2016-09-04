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
#define N 2000000

struct node{
 int bucc;
 bool inve;
 node(){
  bucc=inve=0;
 }
};

char s[N+5];
char haha[105];
char c;
int a,b,k,q,mm,tc,it,len;

struct Stree{
 node seg[4*N+5];
 int size;
 
 inline void resize(int sz){
  size=sz;
 }
 
 inline void build(int sz){
  resize(sz);
  build(0,0,sz);
 }
 
 inline void build(int id,int l,int r){
  if(l==r){
   seg[id].inve=seg[id].bucc=0;
   if(s[l]=='1') seg[id].bucc=1;
  }
  else{
   int m=(l+r)>>1,chld=id<<1;
   build(chld+1,l,m);
   build(chld+2,m+1,r);
   seg[id].bucc=seg[chld+1].bucc+seg[chld+2].bucc;
   seg[id].inve=0;
  }
 }
 
 inline void propagate(int id,int l,int r){
  int m=(l+r)>>1,chld=id<<1;
  if(seg[id].inve){
   seg[chld+1].inve=!(seg[chld+1].inve);
   seg[chld+2].inve=!(seg[chld+2].inve);
   seg[chld+1].bucc=m-l+1-seg[chld+1].bucc;
   seg[chld+2].bucc=r-m-seg[chld+2].bucc;
  }
  seg[id].inve=0;
  if(seg[id].bucc==r-l+1){
   seg[chld+1].bucc=m-l+1;
   seg[chld+2].bucc=r-m;
   seg[chld+1].inve=seg[chld+2].inve=0;
  }
  else if(seg[id].bucc==0){
   seg[chld+1].bucc=0;
   seg[chld+2].bucc=0;
   seg[chld+1].inve=seg[chld+2].inve=0;
  }
 }
 
 inline void update(int l,int r,int op){
  update(0,0,size,l,r,op);
 }
 
 inline void update(int id,int l,int r,int x,int y,int op){
  //if(r-l+1 !=seg[id].bucc+seg[id].barb)
   //cout<<"GAJE "<<id<<" "<<l<<" "<<r<<" "<<seg[id].bucc<<" "<<seg[id].barb<<"\n";
  if(x<=l && r<=y){
   if(op==1)
    seg[id].inve=0,seg[id].bucc=r-l+1;
   else if(op==2)
    seg[id].inve=0,seg[id].bucc=0;
   else
    seg[id].inve=!(seg[id].inve),seg[id].bucc=(r-l+1)-seg[id].bucc;  
  }
  else{
   int m=(l+r)>>1,chld=id<<1;
   if(seg[id].bucc==0 || seg[id].bucc==r-l+1 || seg[id].inve)
    propagate(id,l,r);
   if(x<=m) update(chld+1,l,m,x,y,op);
   if(y>m)  update(chld+2,m+1,r,x,y,op);
   seg[id].bucc=seg[chld+2].bucc+seg[chld+1].bucc;
  }
 }
 
 inline int query(int l,int r){
  return query(0,0,size,l,r);
 } 
 
 inline int query(int id,int l,int r,int x,int y){
  //if(r-l+1 !=seg[id].bucc+seg[id].barb)
   //cout<<"GAJE "<<id<<" "<<l<<" "<<r<<" "<<seg[id].bucc<<" "<<seg[id].barb<<"\n";
  if(x<=l && r<=y) return seg[id].bucc;
  else{
   int m=(l+r)>>1,chld=id<<1,ret=0;
   if(seg[id].inve || seg[id].bucc==0 || seg[id].bucc==r-l+1)
    propagate(id,l,r);
   seg[id].bucc=seg[chld+2].bucc+seg[chld+1].bucc;
   if(x<=m) ret+=query(chld+1,l,m,x,y);
   if(y>m)  ret+=query(chld+2,m+1,r,x,y);
   return ret;
   }
 }
}stree;

inline void GetStr(){
 it=0;
 c=g();
 while(c=='1' || c=='0'){
  haha[it++]=c;
  c=g();
 }
}

int main(){
 tc=io();
 for(int t=1;t<=tc;t++){
  len=0;
  mm=io();
  while(mm--){
   k=io();
   GetStr();
   for(int i=it-1;i>=0;i--)
    for(int j=k-1;j>=0;j--)
     s[len+j*it+i]=haha[i];
   len+=it*k;
  }
  stree.build(len-1);
  q=io();
  printf("Case %d:\n",t);
  it=0;
  while(q--){
   c=g();
   assert(c=='F' || c=='E' || c=='I' || c=='S');
   a=io(); b=io();
   if(c=='F') c=1;
   else if(c=='E') c=2;
   else if(c=='I') c=3;
   else{
    printf("Q%d: %d\n",++it,stree.query(a,b));
    continue;
   }
   //cout<<op<<"\n";
   stree.update(a,b,c);
  }
 }
 //puts("ganteng");
 return 0;
}

