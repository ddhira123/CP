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

struct point{
 double x,y;
 
 
  
 bool operator <(point other) const{
  if(fabs(x-other.x)<EPS)
   return y<other.y;
  return x<other.x; 
 }
 
 bool operator ==(point other) const{
  return fabs(x-other.x)<EPS && fabs(y-other.y)<EPS;
 }
 
};

int n,sz;
int tc;
point arr[105],uni[105];

double cross(double x1,double y1,double x2,double y2){
 double ha= x1*y2- x2*y1;
 //printf("%.2lf\n",fabs(ha));
 return ha;
}

bool coccw(point i,point j,point k){
 return fabs(cross(i.x-j.x,i.y-j.y,i.x-k.x,i.y-k.y)) < EPS;
}

void uniq(){
 sort(arr,arr+n);
 uni[0].x=arr[0].x;
 uni[0].y=arr[0].y;
 sz=1;
 for(int i=1;i<n;i++){
  if(arr[i]==arr[i-1]) continue;
  uni[sz].x=arr[i].x;
  uni[sz++].y=arr[i].y;
  //printf("IDX %d %.2lf %.2lf\n",sz-1,arr[i].x,arr[i].y);
 }
}

int main(){
 scanf("%d",&tc);
 for(int t=1;t<=tc;t++){
  scanf("%d",&n);
  for(int i=0;i<n;i++)
   scanf("%lf %lf",&arr[i].x,&arr[i].y);
  uniq();
  //for(int i=0;i<sz;i++)
   //printf("%.2lf %.2lf\n",uni[i].x,uni[i].y);
  printf("Data set #%d ",t);
  if(sz==1)
   printf("contains a single gnu.\n");
  else{
   int ans=2;
   for(int i=0;i<sz;i++)
    for(int j=i+1;j<sz;j++){
     int ret=2;
     for(int k=j+1;k<sz;k++)
      if(coccw(uni[i],uni[j],uni[k]))
       ret++;
     ans=max(ret,ans);  
    // printf("%d %d %d\n",i,j,ret);
    }
   printf("contains %d gnus, out of which a maximum of %d are aligned.\n",sz,ans); 
  }   
 }
 //puts("ganteng");
 return 0;
}

