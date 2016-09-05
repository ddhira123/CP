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

const int MAXN = 100005;
const int MAX2 = 150000;
const int MAX3 = 225;

int arr[MAXN];
pii arr2[MAXN];
pair<pii,pii> arr3[MAXN];

int BIT2[MAX2+5];
int BIT3[MAX3+5][MAX3+5][MAX3+5];
int n,d,m,op;

void Update2(int x,int val){
 for( ; x <= MAX2 ; x += x & -x)
  BIT2[x] += val;
}

int Query2(int x){
 int ret = 0;
 for( ; x ; x -= x & -x)
  ret += BIT2[x];
 return ret;
}

void Update3(int x,int y,int z,int val){
 for(int i = x ; i <= MAX3 ; i += i & -i)
  for(int j = y ; j <= MAX3 ; j += j & -j)
   for(int k = z ; k <= MAX3 ; k += k & -k)
    BIT3[i][j][k] += val;
}

int Query3(int x,int y,int z){
 int ret = 0;
 for(int i = x ; i ; i -= i & -i)
  for(int j = y ; j ; j -= j & -j)
   for(int k = z ; k ; k -= k & -k)
    ret += BIT3[i][j][k];
 return ret;
}

void Answer1(){
 for(int i = 0 ; i < n ; i++)
  scanf("%d",&arr[i]);
 sort(arr,arr + n);
 LL ans = 0;
 int it = 0;
 for(int i = 0 ; i < n ; i++){
  while(arr[i] - arr[it] > d) it++;
  ans += (i - it);
 }
 printf("%lld\n",ans);
}

void Answer2(){
 int a,b;
 for(int i = 0 ; i < n ; i++){
  scanf("%d %d",&a,&b);
  arr2[i] = mp(a + b, a - b + 75000);
 }
 sort(arr2,arr2 + n);
 LL ans = 0;
 int it = 0;
 for(int i = 0 ; i < n ; i++){
  while(arr2[i].fi - arr2[it].fi > d){
   Update2(arr2[it].se, -1);
   it++;
  }
  b = min(MAX2, arr2[i].se + d);
  a = max(1, arr2[i].se - d);
  int tmp = Query2(b) - Query2(a - 1);
  ans += tmp;
  Update2(arr2[i].se,1);
 }
 printf("%lld\n",ans);
}

void Answer3(){
 int a,b,c;
 for(int i = 0 ; i < n ; i++){
  scanf("%d %d %d",&a,&b,&c);
  arr3[i].fi = mp(a + b + c, a + b - c + 75);
  arr3[i].se = mp(a - b + c + 75, a - b - c + 150);
 }
 //DEBUG;
 sort(arr3,arr3 + n);
 LL ans = 0;
 int it = 0;
 for(int i = 0 ; i < n ; i++){
  //printf("%d\n",i);
  while(arr3[i].fi.fi - arr3[it].fi.fi > d){
   Update3(arr3[it].fi.se, arr3[it].se.fi, arr3[it].se.se, -1);
   it++;
  }
  int xb = min(MAX3,arr3[i].fi.se + d);
  int xa = max(1,arr3[i].fi.se - d);
  int yb = min(MAX3,arr3[i].se.fi + d);
  int ya = max(1,arr3[i].se.fi - d);
  int zb = min(MAX3,arr3[i].se.se + d);
  int za = max(1,arr3[i].se.se - d);
  int tmp = Query3(xb,yb,zb);
  tmp -= (Query3(xa-1,yb,zb) + Query3(xb,ya-1,zb) + Query3(xb,yb,za-1));
  tmp += (Query3(xa-1,ya-1,zb) + Query3(xa-1,yb,za-1) + Query3(xb,ya-1,za-1));
  tmp -= Query3(xa-1,ya-1,za-1);
  ans += tmp;
  Update3(arr3[i].fi.se, arr3[i].se.fi, arr3[i].se.se, 1);
 }
 printf("%lld\n",ans);
}

int main(){
  scanf("%d %d %d %d",&op,&n,&d,&m);
  if(op == 1) Answer1();
  else if(op == 2) Answer2();
  else Answer3();
 //puts("ganteng");
 return 0;
}


