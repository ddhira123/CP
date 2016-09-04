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

double dp[105];
int n;
double e,f,v,b;
int r;
int dist[105];
double prefix[100005];


int main(){
 scanf("%d",&n);
 while(n){
  for(int i=1;i<=n;i++)
   scanf("%d",&dist[i]);
  scanf("%lf",&b);
  scanf("%d %lf %lf %lf",&r,&v,&e,&f);
  for(int i=0;i<=dist[n];i++){
   if(i>=r)
    prefix[i]=1.0/(v-e*(double)(i-r));
   else
    prefix[i]=1.0/(v-f*(double)(r-i));
   if(i) prefix[i]+=prefix[i-1];  
  }
  dp[n]=0.0;
  for(int i=n-1;i>=0;i--){
   dp[i]=20000000000.0;
   for(int j=n;j>i;j--)
    dp[i]=min(dp[i],prefix[dist[j]-dist[i]-1]+dp[j]);
   dp[i]+=b; 
  }
  printf("%.4lf\n",dp[0]-b);
  scanf("%d",&n);
 }
 //puts("ganteng");
 return 0;
}

