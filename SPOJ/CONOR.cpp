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

int tot[605][605],arr[605][605];
int BIT[605][605];
int r,c,q;

inline void Update(int rr,int cc,int v){
 for(int i=rr ; i<=r ; i+= i&-i)
  for(int j=cc ; j<=c ; j+= j&-j)
   BIT[i][j]^=v;
}

inline int Query(int rr,int cc){
 int ans=tot[rr][cc];
 for(int i=rr ; i ; i-= i&-i)
  for(int j=cc ; j ; j-= j&-j)
   ans^=BIT[i][j];
 return ans;  
}

int main(){
 r=io(),c=io();
 for(int i=1; i<=r ; i++)
  for(int j=1 ; j<=c ; j++){
   arr[i][j]=io();
   tot[i][j]=arr[i][j] ^ tot[i-1][j] ^ tot[i][j-1] ^ tot[i-1][j-1];
  }
 q=io();
 while(q--){
  int r1,r2,c1,c2,k;
  k=io();
  if(k){
   r1=io()+1,c1=io()+1,k=io();
   Update(r1,c1,arr[r1][c1]^k);
   arr[r1][c1]=k;
  }
  else{
   r1=io()+1,c1=io()+1,r2=io()+1,c2=io()+1;
   int ret=Query(r2,c2);
   ret^=Query(r2,c1-1);
   ret^=Query(r1-1,c2);
   ret^=Query(r1-1,c1-1);
   printf("%d\n",ret);
  }
 } 
 //puts("ganteng");
 return 0;
}

