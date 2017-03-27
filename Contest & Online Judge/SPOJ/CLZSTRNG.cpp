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

const int md = 1000000009;

void add(int &x,int y){
 x += y;
 if(x >= md) x -= md;
}

int len,m,k;
int tc;
int dp[105][105];
int C[105][105];
char s1[105],s2[105];

int Precompute(){
 for(int i = 0 ; i <= 100 ; i++)
  C[i][0] = 1;
 for(int i = 1 ; i <= 100 ; i++)
  for(int j = 1 ; j <= i ; j++){
   C[i][j] = C[i-1][j];
   add(C[i][j],C[i-1][j-1]);
  } 
 //for(int i = 1 ; i <= 4 ; i++)
  //for(int j = 0 ; j <= i ; j++)
   //printf("C[%d][%d] -> %d\n",i,j,C[i][j]); 
}

int solve(int diff,int left){
 if(left == 0) return (diff == 0);
 int &ret = dp[diff][left];
 if(ret!=-1) return ret;
 ret = 0;
 for(int i = 0 ; i <= min(m,diff) ; i++){
  LL tmp = (LL)C[diff][i]*(LL)C[len-diff][m-i];
  tmp %= (LL)md;
  tmp *= (LL)solve(diff + m - 2*i, left-1);
  tmp %= (LL)md;
  add(ret,tmp); 
 }
 //printf("%d %d -> %d\n",diff,left,ret);
 return ret;
}

int main(){
 Precompute();
 scanf("%d",&tc);
 while(tc--){
  scanf("%s %s",s1,s2);
  scanf("%d %d",&m,&k);
  len = strlen(s1);
  int diff = 0;
  for(int i = 0 ; i < len ; i++)
   diff += (s1[i] != s2[i]);
  for(int i = 0 ; i <= len ; i++)
   for(int j = 0 ; j <= k ; j++) 
    dp[i][j] = -1;
  printf("%d\n",solve(diff,k));  
 }
 //puts("ganteng");
 return 0;
}
