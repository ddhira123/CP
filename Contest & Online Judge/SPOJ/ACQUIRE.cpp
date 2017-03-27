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

pll arr[50005];
vector<pll> v,hull;
int n;
LL dp[50005];

// 0 = (m1-m2)x + (c1-c2)
// x = (c2-c1)/(m1-m2)

bool bad(pll a,pll b,pll c){
 return (b.se - a.se) * (a.fi - c.fi) > (c.se - a.se) * (a.fi - b.fi);
}

int main(){
 scanf("%d",&n);
 for(int i = 0 ; i < n ; i++)
  scanf("%lld %lld",&arr[i].fi,&arr[i].se);
 sort(arr,arr + n);
 
 for(int i = 0 ; i < n ; i++){
  while(!v.empty() && v.back().se <= arr[i].se) v.pop_back();
  v.pb(arr[i]);
 } 
 
 v.pb(mp(INF,0));
 
 hull.pb(mp(v[0].se,0));
 int it = 0;
 
 for(int i = 0 ; i < v.size() - 1 ; i++){
  
  LL x = v[i].fi;
  
  if(it >= hull.size()) it = hull.size() - 1;
  while(it + 1 != hull.size() && hull[it+1].fi * x + hull[it+1].se <= 
        hull[it].fi * x + hull[it].se)
          it++;
   
  dp[i] = hull[it].fi * x + hull[it].se;
  //printf("%d -> %lld %lld dp %lld\n",i,v[i].fi,v[i].se,dp[i]); 
  pll lol = mp(v[i+1].se,dp[i]);
   
  while(hull.size() >= 2 && bad(hull[hull.size()-2],hull.back(),lol)){
   //printf("%lld %lld\n",hull.back().fi,hull.back().se);
   hull.pop_back();
  }
  hull.pb(lol);          
 }
 
 printf("%lld\n",dp[v.size()-2]);
 //puts("ganteng");
 return 0;
}
