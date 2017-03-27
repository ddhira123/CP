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
#define MOD2 1000000014000000049LL
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

struct Matrix{
 LL mat[5][5];
 
 Matrix(){
  memset(mat,0,sizeof mat);
 }
 
 Matrix operator *(Matrix other){
  Matrix res;
  for(int i=0;i<5;i++)
   for(int j=0;j<5;j++)
    for(int k=0;k<5;k++){
     res.mat[i][j] += mat[i][k]*other.mat[k][j];
     if(res.mat[i][j] >= MOD2) res.mat[i][j] -= MOD2;
    }
  for(int i=0;i<5;i++)
   for(int j=0;j<5;j++)
    res.mat[i][j]%=MOD;
   return res;   
 }
 
};

Matrix power[35];
int n,tc,m;

void Precompute(){
 for(int i=0;i<5;i++)
  power[0].mat[0][i]=1;
 for(int i=1;i<5;i++)
  power[0].mat[1][i]=1;
 for(int i=2;i<5;i++)
  power[0].mat[i][i-1]=1;
 for(int i=1;i<30;i++)
  power[i]=power[i-1]*power[i-1];   
}

int modpow(int po){
 if(po<=2) return 0;
 po-=3;
 Matrix ret;
 for(int i=0;i<5;i++)
  ret.mat[i][i]=1;
 int cnt=0;
 while(po){
  if(po&1) ret=ret*power[cnt];
  po>>=1;
  cnt++;
 } 
 int lol=ret.mat[0][0] + ret.mat[0][1];
 if(lol >= MOD) lol-=MOD;
 return lol;
}

int main(){
 Precompute();
 tc=io();
 while(tc--){
  m=io(),n=io();
  int ans=modpow(n) - modpow(m-1);
  if(ans<0) ans+=MOD;
  printf("%d\n",ans);
 }
 //puts("ganteng");
 return 0;
}
