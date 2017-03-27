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

struct node{
 int sum;
 bool rev;
 
 node(){
  sum = 0;
  rev = 0;
 }
};

node stree[4000005];
int n,q,bug;

void Build(int id,int l,int r){
 stree[id].sum = r-l+1;
 stree[id].rev = 0;
 if(l < r){
  int chld = id << 1, m = (l+r)>>1;
  Build(chld,l,m);
  Build(chld+1,m+1,r);
 }
}

void Propagate(int id,int l,int r){
 int chld = id << 1, m = (l+r)>>1;
 stree[chld].rev ^= 1;
 stree[chld+1].rev ^= 1;
 stree[id].rev ^= 1;
 
 stree[chld].sum = m-l+1 - stree[chld].sum;
 stree[chld+1].sum = r-m - stree[chld+1].sum;
}

void Update(int id,int l,int r,int x,int y){
 if(x <= l && r <= y){
  stree[id].sum = r-l+1 - stree[id].sum;
  stree[id].rev ^= 1;
 }
 else{
  int chld = id << 1, m = (l+r)>>1;
  if(stree[id].rev) 
   Propagate(id,l,r);
  if(x <= m) Update(chld,l,m,x,y);
  if(y > m)  Update(chld+1,m+1,r,x,y);
  
  stree[id].sum = stree[chld].sum + stree[chld+1].sum; 
 }
 //printf("%d RANGE %d %d UPDATE %d %d RESULT %d\n",id,l,r,x,y,stree[id].sum);
}

void Query(){
 if(stree[1].sum < bug)
  puts("AC?");
 else{
  int id = 1, l = 1, r = n;
  int tot = 0;
  while(l < r){
   int chld = id << 1, m = (l+r)>>1;
   if(stree[id].rev)
    Propagate(id,l,r);
   if(stree[chld].sum + tot >= bug)
    id = chld, r = m;
   else
    tot += stree[chld].sum, id = chld+1, l = m+1; 
  }
  printf("%d\n",l);
 } 
}

int main(){
 scanf("%d %d %d",&n,&q,&bug);
 Build(1,1,n);
 while(q--){
  int a,b;
  scanf("%d %d",&a,&b);
  Update(1,1,n,a,b);
  Query();
 }
 //puts("ganteng");
 return 0;
}
