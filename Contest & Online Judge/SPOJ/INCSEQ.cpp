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
#define MOD 5000000
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

int BIT[76][100002];
int uniq[100002];
int n,k;
int arr[100002];
int sz;

inline void add(int &x,int y){
 x+=y;
 if(x>=MOD) x-=MOD;
}

inline void Update(int tot,int x,int val){
 for(;x<=sz;x+=x&-x)
  add(BIT[tot][x],val);
}

inline int Query(int tot,int x){
 if(tot==0) return 1;
 int ret=0;
 for(;x;x-=x&-x)
  add(ret,BIT[tot][x]);
 return ret; 
}

inline int ID(int x){
 return lower_bound(uniq,uniq+sz,x) - uniq;
}

int main(){
 n=io(),k=io();
 for(int i=0;i<n;i++)
  arr[i]=io(),uniq[i]=arr[i];
 sort(uniq,uniq+n);
 sz=unique(uniq,uniq+n) - uniq;
 //for(int i=0;i<sz;i++)
  //printf("ID %d -> %d\n",i,uniq[i]);
 for(int i=0;i<n;i++){
  int id=ID(arr[i]);
  //printf("NOW %d\n",i);
  for(int j=0;j<k;j++){
   int lol=Query(j,id);
   //printf("%d -> %d\n",j,lol);
   if(lol)
    Update(j+1,id+1,lol);
  } 
  //printf("NOW %d %d\n",i,Query(k,id)); 
 } 
 int ans=Query(k,sz);
 //for(int i=1;i<=sz;i++)
  //add(ans,Query(k-1,i));//,printf("%d\n",ans);
 printf("%d\n",ans); 
 //puts("ganteng");
 return 0;
}
