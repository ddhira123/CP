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
#define INF 1000000001
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
int n;

struct Node{
 int lazy;
 int sum;
 int maks;
 Node *L,*R;
 Node(){
  lazy=sum=maks=0;
  L=R=NULL;
 }
};

struct SegmentTree{
 
 Node *root;
 
 SegmentTree(){
  root=new Node();
 }
 
 inline int GetM(Node *x){
  return x==NULL ? 0 : x->maks;
 }
 
 inline int GetS(Node *x){
  return x==NULL ? 0 : x->sum;
 }
 
 inline void Propagate(Node *x,int l,int r){
  int m=(l+r)>>1;
  if(x->L==NULL) x->L=new Node();
  if(x->R==NULL) x->R=new Node();
  int v=x->lazy;
  x->L->lazy=v;
  x->R->lazy=v;
  x->L->sum=v*(m-l+1);
  x->R->sum=v*(r-m);
  x->L->maks=max(v,x->L->sum);
  x->R->maks=max(v,x->R->sum);
 }
 
 inline void Update(int l,int r,int v){
  Update(root,0,n,l,r,v);
 }
 
 void Update(Node *now,int l,int r,int x,int y,int v){
  if(x<=l && r<=y){
   now->lazy=v;
   now->sum=v*(r-l+1);
   now->maks=max(v,now->sum);
  }
  else{
   int m=(l+r)>>1;
   if(now->lazy!=INF){
    Propagate(now,l,r);
    now->lazy=INF;
   }
   if(x <= m) Update(now->L,l,m,x,y,v);
   if(y > m)  Update(now->R,m+1,r,x,y,v);
   now->sum=GetS(now->L) + GetS(now->R);
   now->maks=max(GetM(now->L),GetS(now->L)+GetM(now->R));
  }
 }
 
 inline int Query(int x){
  int ans=0;
  int l=0,r=n;
  int tot=0;
  Node *now=root;
  while(l<r){
   if(now->lazy!=INF){
    Propagate(now,l,r);
    now->lazy=INF;
    now->sum=GetS(now->L) + GetS(now->R);
    now->maks=max(GetM(now->L),GetS(now->L) + GetM(now->R));
   }
   int m=(l+r)>>1;
   if(tot + GetM(now->L) <= x){
    ans=m;
    tot+=GetS(now->L);
    now=now->R;
    l=m+1;
   }
   else{
    now=now->L;
    r=m;
   } 
  }
  if(tot+GetM(now)<=x)
   ans=l;
  return ans; 
 }
}Stree;


int main(){
 int a,b,d;
 char op;
 SYNC;
 cin>>n;
 cin>>op;
 //cout<<n<<" "<<op<<"\n";
 while(op!='E'){
  if(op=='Q'){
   cin>>a;
   //cout<<"QQ\n";
   cout<<Stree.Query(a)<<"\n";
  }
 else{
  cin>>a>>b>>d;
  Stree.Update(a,b,d);
 }
 cin>>op; 
 }
 //puts("ganteng");
 return 0;
}

