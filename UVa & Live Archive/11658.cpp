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

double dp[101][10001];
int n,x;
int a,b;
int arr[101];

double solve(int pos,int sum){
 //printf("%d %d\n",pos,sum);
 if(pos>n){
  if(sum<=5000) return 0.0;
  return (double)(100*arr[x])/double(sum);
 }
 double &ret=dp[pos][sum];
 if(ret > -0.5) return ret;
 if(pos==x) ret=solve(pos+1,sum+arr[pos]);
 else ret=max(solve(pos+1,sum),solve(pos+1,sum+arr[pos]));
 return ret;
}

int main(){
 scanf("%d %d",&n,&x);
 while(n|x){
  for(int i=1;i<=n;i++){
   scanf("%d",&a);
   g();
   scanf("%d",&b);
   arr[i]=a*100+b;
   for(int j=0;j<=10000;j++)
    dp[i][j]=-1.0;
  }
  printf("%.2lf\n",solve(1,0));
  scanf("%d %d",&n,&x);
 }
 //puts("ganteng");
 return 0;
}

