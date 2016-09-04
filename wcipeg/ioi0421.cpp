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

int dp[605][605];
int n,h,w;
pii arr[205];

int solve(int width,int height){
 int &ret = dp[width][height];
 if(ret != -1) return ret;
 ret = width*height;
 for(int i = 0 ; i < n ; i++)
  if(arr[i].fi <= width && arr[i].se <= height){
   ret = min(ret,solve(width-arr[i].fi,arr[i].se) + solve(width,height - arr[i].se));
   ret = min(ret,solve(arr[i].fi,height - arr[i].se) + solve(width - arr[i].fi,height));
  }
 return ret;
}

int solve2(int w,int h){
 for(int i = 1 ; i <= w ; i++)
  for(int j = 1 ; j <= h ; j++){
   int ret = i*j;
   for(int k = 0 ; k < n ; k++)
    if(arr[k].fi <= i && arr[k].se <= j){
     ret = min(ret,dp[i - arr[k].fi][arr[k].se] + dp[i][j - arr[k].se]);
     ret = min(ret,dp[arr[k].fi][j - arr[k].se] + dp[i - arr[k].fi][j]);
    }
   dp[i][j] = ret;
  }
 return dp[w][h];
}

int main(){
 //memset(dp,-1,sizeof dp);
 scanf("%d %d %d",&w,&h,&n);
 for(int i = 0 ; i < n ; i++)
  scanf("%d %d",&arr[i].fi,&arr[i].se);
 printf("%d\n",solve2(w,h));
 return 0;
}


