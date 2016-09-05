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
#define makmu using
#define ndasmu namespace
#define gundulmu std

makmu ndasmu gundulmu;

typedef pair<int,int> pii;
typedef long long LL;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SYNC ios_base::sync_with_stdio(false)
#define g getchar_unlocked
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL

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

struct DSU{
 vector<int> par;
 
 inline void reset(int sz){
  par.clear();
  for(int i=0;i<=sz+5;i++)
   par.push_back(i);
 }
 
 int finds(int x){
  return (x==par[x] ? x : par[x]=finds(par[x]) );
 }
 
 bool issame(int x,int y){
  return finds(x)==finds(y);
 }
 
 void uni(int x,int y){
  if(issame(x,y)) return;
  par[finds(y)]=finds(x);
 }
 
 inline int member(int x){
  int ret=0;
  int parent=finds(x);
  for(int i=0;i<par.size();i++)
   ret+=(parent==finds(i));
  return ret; 
 }
};

DSU proc;
int n,m,a,b,c;

int main(){
 n=io(); m=io();
 while(n|m){
  proc.reset(n);
  while(m--){
   c=io(); a=io();
   c--;
   while(c--){
    b=io();
    proc.uni(a,b);
   }
  }
  printf("%d\n",proc.member(0));
  n=io(); m=io();
 }
 //puts("ganteng");
 return 0;
}

