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

LL BIT[2][100005];
int n,q,tc,a,b;
char s[15];

void Update(int id,int x,int val){
 for(; x<=n ; x+= x&-x)
  BIT[id][x]+=val;
}

LL Query(int x){
 LL ret=0,mul=0;
 for(int i = x ; i ; i-= i&-i){
  ret+=BIT[0][i];
  mul+=BIT[1][i];
 }
 return ret*x - mul;
}

int main(){
 tc = io();
 for(int T=1;T<=tc;T++){
  printf("Scenario #%d:\n",T);
  n =io() ; q = io();
  for(int i=1;i<=n;i++)
   BIT[0][i] = BIT[1][i] = 0;
  while(q--){
   scanf("%s",s);
   a = io() ; b = io();
   //assert(a<=b);
   if(s[0] == 'a')
    printf("%lld\n",Query(b) - Query(a-1));
   else{
    puts("OK");
    Update(0,a,1);
    Update(0,b+1,-1);
    Update(1,a,a-1);
    Update(1,b+1,-b);
   } 
  } 
 } 
 //puts("ganteng");
 return 0;
}

