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
#define INF 1000000000000000LL
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

LL dp[15][5005];
LL prime[12]={2,3,5,7,11,13,17,19,23,29,31,37};

void Precompute(){
 for(int i=0;i<=12;i++)
  for(int j=0;j<=5000;j++)
   dp[i][j]=INFLL;
 dp[0][1]=1;
 for(int i=1;i<=12;i++){
  LL mul=1;
  int cnt=1;
  while(mul <= INF){
   for(int j=5000/cnt;j>=1;j--)
    if(dp[i-1][j] <= dp[i][j*cnt]/mul)
     dp[i][j*cnt] = dp[i-1][j]*mul;
   mul*=prime[i-1];
   cnt++;
  }
 }  
}

int main(){
 Precompute();
 int n,tc=0;
 while(scanf("%d",&n)==1){
  if(n==0) break;
  LL ans=dp[12][n];
  printf("Case %d: ",++tc);
  if(ans > INF) puts("Impossible");
  else printf("%lld\n",ans);
 }
 //puts("ganteng");
 return 0;
}

