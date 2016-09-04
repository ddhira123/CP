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

const int md = 10007;

pii arr[15];
int n,tc;
int fact[md+5],inve[md+5];

int modpow(int base){
 int po = md - 2;
 int res = 1;
 while(po){
  if(po & 1) res = (res * base) % md;
  base = (base * base) % md;
  po >>= 1;
 }
 return res;
}

void Precompute(){
 fact[0] = inve[0] = 1;
 for(int i = 1 ; i < md ; i++){
  fact[i] = (fact[i-1] * i) % md;
  inve[i] = modpow(fact[i]);
 }
}

int C(int x,int y){
 if(y > x) return 0;
 int res = fact[x];
 res = (res * inve[y]) % md;
 res = (res * inve[x-y]) % md;
 return res;
}

int solve(int dh,int dw){
 if(dh < 0 || dw < 0) return 0;
 if(dw > dh) swap(dw,dh);
 if((2*dh - dw) % 3 != 0) return 0;
 int x = (2*dh - dw) / 3;
 int y = dh - 2*x;
 if(x < 0 || y < 0) return 0;
 int z = x + y;
 int ans = 1;
 while(z > 0){ // Lucas' Theorem
  ans = (ans * C(z % md, x % md)) % md;
  z /= md;
  x /= md;
 }
 return ans;
}

int main(){
 Precompute();
 scanf("%d",&tc);
 for(int t = 1 ; t <= tc ; t++){
  int h,w;
  scanf("%d %d %d",&h,&w,&n);
  arr[0] = mp(1,1);
  arr[n+1] = mp(h,w);
  for(int i = 1 ; i <= n ; i++)
   scanf("%d %d",&arr[i].fi,&arr[i].se);
  sort(arr,arr+n+2);
  int ans = 0;
  for(int i = 1 ; i < (1 << (n+2)) ; i++)
   if((i & 1) > 0 && (i & (1 << (n+1))) > 0){
    int las = 0;
    int ret = 1;
    for(int j = 1 ; j < n + 2 ; j++)
     if(i & (1 << j)){
      ret = (ret * solve(arr[j].fi - arr[las].fi, arr[j].se - arr[las].se)) % md;
      las = j;
     }
    if(__builtin_popcount(i) & 1)
     ans -= ret;
    else
     ans += ret;
   }
  ans %= md;
  if(ans < 0) ans += md;
  printf("Case #%d: %d\n",t,ans);
 }
 return 0;
}
