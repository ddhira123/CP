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

int tc,n;
LL x;
LL uni[1000005];
int BIT[1000005];
LL arr[500005];
int len;
int ans;

inline void update(int x,int v){
 for(;x<=len;x+=x&-x)
  BIT[x]=v;
}

inline int query(int x){
 int ret=-INF;
 for(;x;x-=x&-x)
  ret=max(ret,BIT[x]);
 return ret; 
}

int main(){
 tc=io();
 while(tc--){
  n=io(),x=io();
  LL maks=-2*INF,sum=0;
  for(int i=0;i<n;i++){
   arr[i]=io();
   sum+=arr[i];
   maks=max(maks,sum);
   sum=max(sum,0LL);
   arr[i]+=arr[i-1];
   uni[(i<<1)]=arr[i];
   uni[(i<<1)|1]=arr[i]-x;
  }
  if(maks>=x){
  uni[n<<1]=0;
  sort(uni,uni+2*n+1);
  len=unique(uni,uni+2*n+1)-uni;
  for(int i=0;i<=len;i++)
   BIT[i]=-INF;
  int id,res;
  id=lower_bound(uni,uni+len,0)-uni;
  update(id+1,-1);
  ans=INF;
  for(int i=0;i<n;i++){
   id=lower_bound(uni,uni+len,arr[i]-x)-uni;
   res=i-query(id+1);
   //printf("%d %d\n",i,res);
   ans=min(ans,res);
   id=lower_bound(uni,uni+len,arr[i])-uni;
   update(id+1,i);
   }
  } 
  else ans=-1;
  printf("%d\n",ans);
 }
 //puts("ganteng");
 return 0;
}

