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

const int MAXX = 1300000;

bool flag[MAXX + 5];
int prime[100010];
pii stek[100010];
int prime_size;
int stek_size;
int n,m,tc;

void Gen(){
 for(int i = 2 ; i <= MAXX ; i++)
  if(!flag[i]){
   prime[++prime_size] = i;
   for(int j = i ; j <= MAXX/i ; j++)
    flag[i*j] = 1;
  }
}

void add(int &x,int y,int md){
 x+=y;
 while(x>=md) x-=md;
}

void Process(){
 int ans = 0;
 scanf("%d %d",&n,&m);
 stek_size = 0;
 for(int i = 1 ; i <= n ; i++){
  stek[++stek_size] = mp(prime[i]%m,1);
  while(stek_size > 1 && stek[stek_size].fi >= stek[stek_size-1].fi){
   add(stek[stek_size].se,stek[stek_size-1].se,m);
   stek[stek_size-1] = stek[stek_size];
   stek_size--;
  }
  //printf("%d %d\n",stek[stek_size].fi,stek[stek_size].se);
  add(ans,stek[stek_size].se,m);
 } 
 printf("%d\n",ans);
}

int main(){
 Gen();
 scanf("%d",&tc);
 while(tc--)
  Process();
 //puts("ganteng");
 return 0;
}

