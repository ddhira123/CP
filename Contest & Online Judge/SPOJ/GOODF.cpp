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

const int MAXN = 1000005;

pair<pii,int> arr[MAXN];
int cost[MAXN];
pii team[MAXN];
int n,m;
pii origin;
LL ans[MAXN];

int dist(pii a,pii b){
 return abs(b.fi - a.fi) + abs(b.se - a.se);
}

int gcd(int a,int b){
 return b ? gcd(b,a%b) : a;
}

bool cmp(pair<pii,int> a,pair<pii,int> b){
 return a.fi == b.fi ? dist(team[a.se],origin) < dist(team[b.se],origin) : a.fi < b.fi;
}

void Build(){
 for(int i = 1 ; i <= n ; i++){
  int xx = team[i].fi - origin.fi;
  int yy = team[i].se - origin.se;
  int div = abs(gcd(xx,yy));
  //printf("%d -> %d %d %d %d %d\n",i,team[i].fi,team[i].se,xx,yy,div);
  xx /= div;
  yy /= div;
  arr[i].fi.fi = yy;
  arr[i].fi.se = xx;
  arr[i].se = i;
 }
 sort(arr+1, arr+n+1, cmp);
 pii tmp = arr[1].fi;
 LL lol = 0;
 for(int i = 1 ; i <= n ; i++){
  int idx = arr[i].se;
  if(tmp == arr[i].fi)
   lol += (LL)cost[idx];
  else
   tmp = arr[i].fi, lol = cost[idx];
  ans[idx] = lol;  
 }
}


int main(){
 scanf("%d %d %d %d",&n,&m,&origin.fi,&origin.se);
 for(int i = 1 ; i <= n ; i++)
  scanf("%d %d %d",&team[i].fi,&team[i].se,&cost[i]);
 Build();
 while(m--){
  int x;
  scanf("%d",&x);
  printf("%lld\n",ans[x]);
 } 
 //puts("ganteng");
 return 0;
}
