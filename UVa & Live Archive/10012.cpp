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

int tmp[10];
double x[10],r[10];
int n;

double sqr(double y){
 return y*y;
}

double brute(){
 double ans=2000000000.0;
 do{
  x[0]=r[tmp[0]];
  double ret=x[0]+x[0];
  for(int i=1;i<n;i++){
   x[i]=r[tmp[i]];
   for(int j=0;j<i;j++)
    x[i]=max(x[i],x[j]+2.0*sqrt(r[tmp[i]]*r[tmp[j]]) ); 
   ret=max(ret,x[i]+r[tmp[i]]); 
  }
  ans=min(ans,ret);
 }while(next_permutation(tmp,tmp+n));
 return ans;
}

int main(){
 int tc;
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(int i=0;i<n;i++)
   tmp[i]=i,scanf("%lf",&r[i]);
  printf("%.3lf\n",brute()); 
 }
 //puts("ganteng");
 return 0;
}

