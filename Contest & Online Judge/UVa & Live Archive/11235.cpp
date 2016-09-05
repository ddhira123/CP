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

int n,q;
int st[200005],jum[200005],en[200005];
int arr[200005],Stree[800005];

void Build(int id,int l,int r){
 if(l==r)
  Stree[id]=jum[l];
 else{
  int m=(l+r)>>1,chld=id<<1;
  Build(chld,l,m);
  Build(chld|1,m+1,r);
  Stree[id]=max(Stree[chld],Stree[chld|1]);
 }
}  
 
int Query(int id,int l,int r,int x,int y){
 if(x<=l && r<=y)
  return Stree[id];
 else{
  int m=(l+r)>>1,chld=id<<1;
  int ret=0;
  if(x<=m) ret=Query(chld,l,m,x,y);
  if(y>m)  ret=max(ret,Query(chld|1,m+1,r,x,y));
  return ret;
  } 
}

int main(){
 n=io();
 for(int i=0;i<=200000;i++)
  st[i]=INF;
 while(n){
  q=io();
  for(int i=1;i<=n;i++){
   arr[i]=io();
   if(st[arr[i]+100000]==INF) st[arr[i]+100000]=i;
   en[arr[i]+100000]=i;
   jum[arr[i]+100000]++;
  }
  Build(1,0,200000);
  while(q--){
   int a,b;
   a=io(),b=io();
   int ans=0;
   if(arr[a]==arr[b])
    ans=b-a+1;
   else if(arr[a]+1==arr[b])
    ans=max(en[arr[a]+100000]-a,b-st[arr[b]+100000])+1;
   else{
    ans=max(en[arr[a]+100000]-a,b-st[arr[b]+100000])+1;
    ans=max(ans,Query(1,0,200000,arr[a]+100001,arr[b]+99999));   
   }
   printf("%d\n",ans);  
  }
  for(int i=1;i<=n;i++)
   jum[arr[i]+100000]=0,st[arr[i]+100000]=INF;
  n=io();
 }
 //puts("ganteng");
 return 0;
}

