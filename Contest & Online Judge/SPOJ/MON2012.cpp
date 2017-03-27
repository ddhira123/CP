#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct node{
 int sum;
 int l,r;
}tmp;

int c,x,y,op,q,sz;

vector<node> stree;

int size(int z){
 if(z==-1) return 0;
 return stree[z].sum;
}

void update(int id,int l,int r){
 if(stree[id].sum==r-l+1) return;
 else if(x<=l && r<=y)
  stree[id].sum=r-l+1;
 else{
  int m=(l+r)>>1;
  if(x<=m){
   if(stree[id].l==-1) stree[id].l=++sz,stree.push_back(tmp);
   update(stree[id].l,l,m);
  }
  if(y>m){
   if(stree[id].r==-1) stree[id].r=++sz,stree.push_back(tmp);
   update(stree[id].r,m+1,r);
  }
  stree[id].sum=size(stree[id].l)+size(stree[id].r);
 }
}

int query(int id,int l,int r){
 if(x<=l && r<=y)
  return stree[id].sum;
 else if(stree[id].sum==r-l+1)
  return min(r,y)-max(l,x)+1;
 else{
  int ret=0,m=(l+r)>>1;
  if(x<=m && stree[id].l!=-1) ret+=query(stree[id].l,l,m);
  if(y>m  && stree[id].r!=-1) ret+=query(stree[id].r,m+1,r);
  return ret;
 }
}

#define g getchar_unlocked
inline int io(){
 char c;
 while(1){
  c=g();
  if(c!=' '&& c!='\n') break;
 }
 int op=1,ret=0;
 if(c=='-') op=-1;
 else ret=c-'0';
 while(1){
  c=g();
  if(c==' '|| c=='\n'||c==EOF) break;
  ret=(ret<<3)+(ret<<1)+c-'0';
 }
 return ret*op;
}

int main(){
 tmp.sum=0,tmp.l=tmp.r=-1;
 stree.push_back(tmp);
 q=io();
 while(q--){
  op=io(); x=io(); y=io();
  x+=c;y+=c;
  if(op==2) update(0,1,1000000000);
  else{
   c=query(0,1,1000000000);
   printf("%d\n",c);
  }
 }
 return 0;
}
