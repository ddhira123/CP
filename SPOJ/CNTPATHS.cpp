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

struct Matrix{
 int sz;
 LL mat[30][30];

 Matrix(){}

 Matrix(int x){
  sz = x;
  for(int i = 0 ; i <= x ; i++)
   for(int j = 0 ; j <= x ; j++)
    mat[i][j] = 0;
 }

 Matrix operator *(Matrix other) const{
  Matrix ret = Matrix(sz);
  for(int i = 0 ; i <= sz ; i++)
   for(int j = 0 ; j <= sz ; j++)
    for(int k = 0 ; k <= sz ; k++){
     ret.mat[i][j] += mat[i][k] * other.mat[k][j];
     if(ret.mat[i][j] >= MOD) ret.mat[i][j]%=MOD;
    }
  return ret;
 }

 Matrix operator ^(int po) const{
  Matrix ret = Matrix(sz);
  Matrix base = Matrix(sz);
  for(int i = 0 ; i <= sz ; i++){
   for(int j = 0 ; j <= sz ; j++)
    base.mat[i][j] = mat[i][j];
   ret.mat[i][i] = 1;
  }

  while(po){
   //printf("PANGKAT %d\n",po);
   //printf("ret\n");
   //ret.Print();
   //printf("base\n");
   //base.Print();
   if(po & 1) ret = ret*base;
   base = base*base;
   po >>= 1;
  }
  return ret;
 }

 void Print(){
  for(int i = 0 ; i <= sz ; i++){
   for(int j = 0 ; j <= sz ; j++)
    printf("%lld ",mat[i][j]);
   puts("");
  }
 }
};

int main(){
 int tc;
 scanf("%d",&tc);
 for(int T = 1 ; T <= tc ; T++){
  int n,t;
  char s[10];
  scanf("%d %d",&n,&t);

  Matrix ans = Matrix(3*n);
  for(int i = 0 ; i < n ; i++)
   for(int j = 0 ; j < 2 ; j++)
    ans.mat[3*i + j][3*i + j + 1] = 1;
  ans.mat[3*n][3*n] = 1;
  ans.mat[3][3*n] = 1;
  for(int i = 0 ; i < n ; i++){
   scanf("%s",s);
   for(int j = 0 ; j < n ; j++)
    if(s[j] != '-'){
     //printf("%d %d\n",3*i + s[j] -'1',3*j);
     ans.mat[3*i + s[j]-'1'][3*j] = 1;
    }
  }

  //puts("AWAL");
  //ans.Print();
  ans = ans^(t+1);
  //puts("AKHIR");
  //ans.Print();
  printf("Case #%d: %lld\n",T,ans.mat[0][3*n]);
 }
}
