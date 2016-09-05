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

double dp[1005][1005];
double dist[1005][1005];
pii arr[1005];
int n;

double solve(int l,int r){
 if(l==n-1 || r==n-1)
  return dist[l][r];
 double &ret=dp[l][r];
 if(ret > -0.5) return ret;
 int m=max(l,r)+1;
 return ret=min(dist[l][m]+solve(m,r),dist[r][m]+solve(l,m)); 
}

int main(){

 while(scanf("%d",&n)==1){
  for(int i=0;i<n;i++){
   scanf("%d %d",&arr[i].fi,&arr[i].se);
   for(int j=n-1;j>=0;j--)
    dp[i][j]=-1.0;
  }
  for(int i=0;i<n;i++)
   for(int j=0;j<n;j++)
    dist[i][j]=hypot(arr[i].fi-arr[j].fi,arr[i].se-arr[j].se);
  sort(arr,arr+n);
  printf("%.2lf\n",solve(0,0));
  //scanf("%d",&n);
 }
 //puts("ganteng");
 return 0;
}

