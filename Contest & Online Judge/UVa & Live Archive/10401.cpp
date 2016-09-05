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

LL dp[20][20];
char s[20];
int len;

int val(char x){
 if(x <= '9') return x-'0';
 else return x- 'A' + 10;
}

LL solve(int row,int col){
 if(col + 1 == len) return 1;
 LL &ret=dp[row][col];
 if(ret!=-1) return ret;
 ret=0;
 if(s[col+1]!='?'){
  if(abs(row - val(s[col+1])) >= 2)
   ret=solve(val(s[col+1]),col+1);
 }
 else
  for(int i=1;i<=len;i++)
   if(abs(row - i) >= 2)
    ret+=solve(i,col+1);
 return ret;   
}

int main(){
 while(scanf("%s",s)!=EOF){
  len=strlen(s);
  memset(dp,-1,sizeof dp);
  LL ans=0;
  if(s[0]!='?')
   ans=solve(val(s[0]),0);
  else
   for(int i=1;i<=len;i++) 
    ans+=solve(i,0);
  printf("%lld\n",ans);  
 }
 //puts("ganteng");
 return 0;
}

