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





int Stree[270005];
int BIT[17][100005];
int po[100005];
int arr[100005];
int n,q,u,v;
char s[5];

void Give(int id){
 int chld=id<<1;
 LL a=Stree[chld],b=Stree[chld+1];
 LL ret=(a+b+a*b)%MOD;
 Stree[id]=ret;
}

void Build(int id,int l,int r){
 if(l==r){
  //maks=max(maks,id)
  Stree[id]=arr[l];
 }
 else{
  int chld=id<<1,m=(l+r)>>1;
  Build(chld,l,m);
  Build(chld+1,m+1,r);
  Give(id);
 }
}

void Update(int id,int l,int r,int x){
 if(l==r){
  Stree[id]=arr[l];
 }
 else{
  int chld=id<<1,m=(l+r)>>1;
  if(x<=m) Update(chld,l,m,x);
  else     Update(chld+1,m+1,r,x);
  Give(id);
 }
}

int Query1(int id,int l,int r,int x,int y){
 if(x<=l && r<=y)
  return Stree[id];
 else{
  int chld=id<<1,m=(l+r)>>1;
  LL q1=0,q2=0,ret=0;
  if(x<=m){
   q1=Query1(chld,l,m,x,y);
   ret=q1;
  }
  if(y > m){
   q2=Query1(chld+1,m+1,r,x,y);
   ret+=q2;
  }
  ret=(ret+q1*q2)%MOD;
  return ret;
 } 
}

void Update2(int id,int val){
 for(int i=0;i<17;i++)
  if(arr[id]&(1<<i))
   for(int j=id;j<=n;j+=j&-j){
    BIT[i][j]+=val;
   }
}



int Query2(int l,int r){
 LL ans=0;
 for(int i=0;i<17;i++){
  int haha=0;
  for(int j=r;j;j-=j&-j)
   haha+=BIT[i][j];
  for(int j=l-1;j;j-=j&-j)
   haha-=BIT[i][j];
  ans+=(1LL<<i)*(po[haha]-1LL);
  ans%=MOD;  
  //printf("%d %d %lld\n",i,haha,ans);
 }
 return ans;
}

int main(){
 scanf("%d",&n);
 po[0]=1;
 for(int i=1;i<=n;i++){
  scanf("%d",&arr[i]);
  Update2(i,1);
  po[i]=po[i-1]<<1;
  if(po[i]>=MOD) po[i]-=MOD;
 } 
 Build(1,1,n);
 scanf("%d",&q);
 while(q--){
  scanf("%s",s);
  scanf("%d %d",&u,&v);
  if(s[0]=='U'){
   Update2(u,-1);
   arr[u]=v;
   Update2(u,1);
   Update(1,1,n,u);
  }
  else if(s[0]=='M'){
   printf("%d\n",Query1(1,1,n,u,v));
   }
  else{
   printf("%d\n",Query2(u,v));
  } 
 } 
 //puts("ganteng");
 return 0;
}

