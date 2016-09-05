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

LL mat[65],tgt;
int tc,n,m,a,b;
LL ret;
int maks;

void rec(int pos,LL mask,int jum){
 //printf("%d %lld %d\n",pos,mask,jum);
 if(mask==tgt){
  ret++;
  maks=max(maks,jum);
 }
 else if(pos<n){
  rec(pos+1,mask,jum);
  if((mask&(1LL<<pos))==0)
   rec(pos+1,mask|mat[pos],jum+1);
 }
}

int main(){
 tc=io();
 while(tc--){
  ret=maks=0;
  n=io(),m=io();
  for(int i=0;i<n;i++)
   mat[i]=(1LL<<i);
 // puts("BB"); 
  while(m--){
   //printf("AA\n");
   a=io(),b=io();
   mat[a]|=(1LL<<b);
   mat[b]|=(1LL<<a);
  }
  tgt=(1LL<<n)-1LL;
  rec(0,0,0);
  printf("%lld\n%d\n",ret,maks); 
 }
 //puts("ganteng");
 return 0;
}

