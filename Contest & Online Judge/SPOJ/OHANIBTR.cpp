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

int lis[MAXN],sz;
int isi[MAXN],pos[MAXN];
int cnt,n,tc;

void DFS(int now){
 if(now > n) return;
 DFS(now*2);
 pos[cnt] = now;
 isi[now] = cnt++;
 //printf("NOW -> %d ISI %d\n",now,isi[now]);
 DFS(now*2 + 1);
}

void Read(){
 sz = 0;
 lis[0] = INF;
 //scanf("%d",&n);
 n = io();
 int a;
 for(int i = 1 ; i <= n ; i++){
  //scanf("%d",&a);
  a = io();
  if(a > lis[sz]) lis[++sz] = a;
  else{
   int lo = 0, hi = sz;
   while(lo < hi){
    int mi = (lo + hi)/2;
    if(lis[mi] >= a) hi = mi;
    else lo = mi + 1;
   }
   lis[lo] = a;
  }
 }
 printf("Minimum Move: %d\n",n-sz-1);
}

void Process(){
 cnt = 1;
 DFS(1);
 printf("%d",isi[pos[1]/2]);
 for(int i = 2 ; i <= n ; i++)
  printf(" %d",isi[pos[i]/2]);
 puts("");
}

int main(){
 isi[0] = -1;
 //scanf("%d",&tc);
 tc = io();
 for(int t = 1 ; t <= tc ; t++){
  printf("Case %d:\n",t);
  Read();
  Process();
 }
 return 0;
}
