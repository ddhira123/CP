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
#define MOD 1000000009LL
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
 LL mat[3][3];
};

matrix matmul(matrix a,matrix b){
 matrix res;
 int i,j,k;
 for(i=0;i<3;i++)
  for(j=0;j<3;j++)
   for(res.mat[i][j]=k=0;k<3;k++)
    res.mat[i][j]=(res.mat[i][j]+a.mat[i][k]*b.mat[k][j])%MOD;
  return res;  
}

matrix matpow(matrix base,LL po){
 matrix res;
 for(int i=0;i<3;i++)
  for(int j=0;j<3;j++)
   res.mat[i][j]=(i==j);
 while(po){
  if(po&1) res=matmul(res,base);
  po>>=1;
  base=matmul(base,base);
 }
 return res;
}

LL n;

int main(){
 SYNC;
 cin>>n;
 while(n){
  if(n==1)
   cout<<"0\n";
  else if(n==2)
   cout<<"1\n";
  else{
   matrix ret;
   ret.mat[0][0]=1;ret.mat[0][1]=1;ret.mat[0][2]=1;
   ret.mat[1][0]=1;ret.mat[1][1]=0;ret.mat[1][2]=0;
   ret.mat[2][0]=0;ret.mat[2][1]=1;ret.mat[2][2]=0;
   ret=matpow(ret,n-3);
   LL ans=2LL*ret.mat[0][0]+ret.mat[0][1];
   ans%=MOD;
   cout<<ans<<"\n";
  }  
  cin>>n;
 }
 //puts("ganteng");
 return 0;
}

