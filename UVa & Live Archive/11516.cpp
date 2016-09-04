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

double arr[100005];
int tc,m,n;

bool valid(double dis){
 double las=-2000000.0;
 int use=0;
 for(int i=0;i<n;i++){
  if(fabs(las-arr[i])<dis+EPS) continue;
  las=arr[i]+dis;
  use++;
  if(use>m) return 0;
 }
 return 1;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d",&m,&n);
  for(int i=0;i<n;i++)
   scanf("%lf",&arr[i]);
  sort(arr,arr+n);
  double lo=0.0,hi=2000000.0;
  while(fabs(lo-hi)>1e-3){
   double mid=(lo+hi)/2.0;
   if(valid(mid)) hi=mid;
   else           lo=mid;
  } 
  printf("%.1lf\n",lo);
 }
 //puts("ganteng");
 return 0;
}

