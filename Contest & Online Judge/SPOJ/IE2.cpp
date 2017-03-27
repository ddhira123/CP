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

const int MAXN = 20;
const LL md = 1000000009;
int n,m,l,d;

struct Matrix{
 LL mat[MAXN][MAXN];

 Matrix(){
  memset(mat, 0, sizeof mat);
 }

 Matrix operator *(Matrix other) const{
  Matrix ret;
  for(int i = 0 ; i < n ; i++)
   for(int j = 0 ; j < n ; j++)
    for(int k = 0 ; k < n ; k++)
     ret.mat[i][j] = (ret.mat[i][j] + mat[i][k] * other.mat[k][j]) % md;
  return ret;
 }

 Matrix operator ^(int po) const{
  Matrix base,ret;
  for(int i = 0 ; i < n ; i++){
   ret.mat[i][i] = 1;
   for(int j = 0 ; j < n ; j++)
    base.mat[i][j] = mat[i][j];
  }

  while(po){
   if(po & 1) ret = ret * base;
   base = base * base;
   po >>= 1;
  }

  return ret;
 }

 void Print(){
  for(int i = 0 ; i < n ; i++){
   for(int j = 0 ; j < n ; j++)
    printf("%lld ",mat[i][j]);
   puts("");
  }
 }
};

int main(){
 scanf("%d %d %d %d",&n,&m,&l,&d);
 d--;
 Matrix awal;
 while(m--){
  int a,b;
  scanf("%d %d",&a,&b);
  awal.mat[a-1][b-1] = awal.mat[b-1][a-1] = 1;
 }
 int ans = 0;
 if(d){
    for(int i = 0 ; i < (1 << l) ; i++){
        Matrix res = awal;
        for(int j = 0 ; j < l ; j++)
            if((i & (1 << j)) != 0)
                for(int k = 0 ; k < n ; k++)
                    res.mat[j][k] = res.mat[k][j] = 0;
        res = res^d;
        int tot = 0;
        for(int j = 0 ; j < n ; j++)
            for(int k = 0 ; k < n ; k++){
                tot += res.mat[j][k];
                if(tot >= md) tot -= md;
           }
        if(__builtin_popcount(i) & 1) ans -= tot;
        else ans += tot;
        if(ans >= md) ans -= md;
        if(ans < 0) ans += md;
    }
 }
 else
  ans = l;
 printf("%d\n",ans);
 return 0;
}
