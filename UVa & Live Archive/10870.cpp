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

struct matrix{
 LL mat[16][16];
 matrix(){
  memset(mat,0,sizeof mat);
 }
};

LL d,n,m;
LL f[20],x[20];

inline matrix matmul(matrix a,matrix b){
 matrix ret;
 for(int i=0;i<d;i++)
  for(int j=0;j<d;j++)
   for(int k=0;k<d;k++)
    ret.mat[i][j]=(ret.mat[i][j]+a.mat[i][k]*b.mat[k][j])%m;
 return ret;   
}

inline matrix matpow(matrix base,int po){
 matrix ret;
 for(int i=0;i<d;i++)
  ret.mat[i][i]=1;
 while(po){
  if(po&1) ret=matmul(ret,base);
  po>>=1;
  base=matmul(base,base);
 }
 return ret;
}

int main(){
 SYNC;
 cin>>d>>n>>m;
 while(d|n|m){
  for(int i=0;i<d;i++)
   cin>>x[i],x[i]%=m;
  for(int i=0;i<d;i++)
   cin>>f[i],f[i]%=m;
  LL ans=0;
  if(n<=d)
   ans=f[n-1]%m;
  else{
   matrix ret;
   for(int i=0;i<d;i++)
    ret.mat[0][i]=x[i];
   for(int i=1;i<d;i++)
    ret.mat[i][i-1]=1;
   /*for(int i=0;i<d;i++){
    for(int j=0;j<d;j++)
     cout<<ret.mat[i][j]<<" ";
    cout<<"\n"; 
   }*/
   ret=matpow(ret,n-d);
   /*for(int i=0;i<d;i++){
    for(int j=0;j<d;j++)
     cout<<ret.mat[i][j]<<" ";
    cout<<"\n"; 
   } */
   for(int i=0;i<d;i++)
    ans=(ans+ret.mat[0][i]*f[d-1-i])%m;  
  }
  if(ans<0) ans+=m;
  cout<<ans<<"\n";   
  cin>>d>>n>>m;
 }
 //puts("ganteng");
 return 0;
}

