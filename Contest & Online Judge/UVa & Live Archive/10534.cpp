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

int BIT[2][10005]; //0 -> LIS , 1 -> LDS
pii arr[10005];
int n;
int LIS[10005],LDS[10005];

bool cmp(pii a,pii b){
 if(a.fi==b.fi)
  return a.se>b.se;
 return a.fi<b.fi; 
}

bool cmp2(pii a,pii b){
 if(a.fi==b.fi)
  return a.se<b.se;
 return a.fi<b.fi; 
}

inline int query(int id,int x){
 int ret=0;
 while(x){
  ret=max(ret,BIT[id][x]);
  x-=x&-x;
  //printf("%d\n",x);
 }
 return ret;
}

inline void update(int id,int x,int v){
 for(int i=x;i<=n;i+=i&-i)
  BIT[id][i]=max(BIT[id][i],v);
}

int main(){
 while(scanf("%d",&n)==1){
  for(int i=1;i<=n;i++){
   BIT[0][i]=BIT[1][i]=0;
   scanf("%d",&arr[i].fi);
   arr[i].se=i;
  }
  //puts("ST");
  sort(arr+1,arr+n+1,cmp);
  //puts("EN");
  for(int i=1;i<=n;i++){
   int pos=arr[i].se;
   LIS[pos]=1+query(0,pos);
   update(0,pos,LIS[pos]);
  }
  sort(arr+1,arr+n+1,cmp2);
  for(int i=1;i<=n;i++){
   int pos=arr[i].se;
   //printf("NOW %d NUM %d POS %d\n",i,arr[i].fi,arr[i].se);
   LDS[pos]=1+query(1,n-pos+1);
   update(1,n-pos+1,LDS[pos]);
  }
  int ans=0;
  for(int i=1;i<=n;i++){
   ans=max(ans,min(LIS[i],LDS[i]));
   //printf("NOW %d -> LIS %d LDS %d\n",i,LIS[i],LDS[i]);
  }
  printf("%d\n",2*ans-1); 
 }
 //puts("ganteng");
 return 0;
}

