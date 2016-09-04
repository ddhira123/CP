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

bool Prime[1000005];
int Prefix[1000005];
int a,b;

inline void Shive(){
 Prime[1]=1;
 for(int i=2;i<=1000000;i++)
  if(!Prime[i])
   for(int j=i;j<=1000000/i;j++)
    Prime[i*j]=1;
}

inline bool Circular(int x){
 int tmp=x,ctr=0,po=1;
 while(tmp)
  ctr++,tmp/=10,po*=10;
 po/=10; 
 for(int i=0;i<ctr;i++){
  if(Prime[x]) return 0;
  int las=x%10;
  x/=10;
  x+=las*po;
 }
 return 1; 
}

inline void Pre(){
 for(int i=2;i<=1000000;i++)
  Prefix[i]=Prefix[i-1]+Circular(i);
}

int main(){
 Shive();
 Pre();
 //SYNC;
 a=io();
 while(a!=-1){
  b=io();
  int ans=Prefix[b]-Prefix[a-1];
  if(ans==0)
   puts("No Circular Primes.");
  else if(ans==1) 
   puts("1 Circular Prime.");
  else
   printf("%d Circular Primes.\n",ans); 
  a=io();
 }
 //puts("ganteng");
 return 0;
}

