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

pair<vector<pii>,int> stree[800005];
int arr[200005];
int n,q,tc;

inline pair<vector<pii>,int> Merge(pair<vector<pii>,int > a,pair<vector<pii>,int > b){
 int i=0,j=0;
 vector<pii> ret;
 int mins=min(a.se,b.se);
 while(i < a.fi.size() && j < b.fi.size() && mins){
  mins=min(mins,abs(a.fi[i].fi-b.fi[j].fi));
  if(a.fi[i].fi < b.fi[j].fi)
   ret.pb(a.fi[i++]);
  else if(a.fi[i].fi > b.fi[j].fi)
   ret.pb(b.fi[j++]);
  else
   ret.pb(mp(a.fi[i].fi,a.fi[i].se+b.fi[j].se)),i++,j++;  
 }
 if(mins){
 while(i < a.fi.size()) ret.pb(a.fi[i++]);
 while(j < b.fi.size()) ret.pb(b.fi[j++]);
 }
 return mp(ret,mins);
}

void Build(int id,int l,int r){
 stree[id].fi.clear();
 if(l==r){
   stree[id].fi.pb(mp(arr[l],1)),stree[id].se=INF;
 }
 else{
  int m=(l+r)>>1,chld=id<<1;
  Build(chld,l,m);
  Build(chld|1,m+1,r);
  stree[id]=Merge(stree[chld],stree[chld|1]);
 }
}

pair<vector<pii>,int> Query(int id,int l,int r,int x,int y){
 if(x<=l && r<=y)
  return stree[id];
 else{
  int m=(l+r)>>1,chld=id<<1;
  pair<vector<pii>,int> ret;
  ret.se=INF;
  if(x<=m && ret.se) ret=Merge(ret,Query(chld,l,m,x,y));
  if(y>m && ret.se)  ret=Merge(ret,Query(chld|1,m+1,r,x,y));
  return ret;
 } 
}

int main(){
 tc=io();
 while(tc--){
  n=io();
  for(int i=1;i<=n;i++)
   arr[i]=io();
  Build(1,1,n);
  q=io();
  while(q--){
   int a=io(),b=io();
   if(b - a + 1 > 10000)
    puts("0");
   else{
    pair<vector<pii>,int> ret=Query(1,1,n,a,b);
    printf("%d\n",ret.se);
   } 
  } 
 }
 //puts("ganteng");
 return 0;
}

