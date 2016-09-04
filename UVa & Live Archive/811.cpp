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

struct point{
 int x;int y;
};

bool cmp(point i,point j){
 return i.x<j.x ||(i.x==j.x && i.y<j.y);
}

bool eq(point i,point j){
 return i.x==j.x && i.y==j.y;
}

vector<point> CHull,proc;
point arr[20];
int n,v[20];
double length[20];
int tc;

inline int cross(int x1,int y1,int x2,int y2){
 return x1*y2-x2*y1;
}

inline bool ccw(point i,point j,point k){
 return cross(i.x-j.x,i.y-j.y,i.x-k.x,i.y-k.y) > 0;
}

inline void MonotoneChain(){
 sort(proc.begin(),proc.end(),cmp);
 proc.erase(unique(proc.begin(),proc.end(),eq),proc.end());
 point head=proc[0],tail=proc.back();
 vector<point> up,down;
 up.pb(head),down.pb(head);
 int szu=1,szd=1;
 for(int i=1;i<proc.size();i++){
  if(i==proc.size()-1 || !ccw(tail,head,proc[i])){
   while(szu>=2 && ccw(up[szu-2],up[szu-1],proc[i]))
    up.pop_back(),szu--;
   szu++;
   up.pb(proc[i]); 
  }
  
  if(i==proc.size()-1 || ccw(tail,head,proc[i])){
   while(szd>=2 && !ccw(down[szd-2],down[szd-1],proc[i]))
    down.pop_back(),szd--;
   szd++;
   down.pb(proc[i]); 
  }
 }
 CHull.clear();
 for(int i=0;i<szu;i++)
  CHull.pb(up[i]);
 for(int i=szd-2;i>0;i--)
  CHull.pb(down[i]);  
}

double dist(point i,point j){
 return hypot(i.x-j.x,i.y-j.y);
}

double Perimeter(){
 double res=0;
 for(int i=1;i<CHull.size();i++)
  res+=dist(CHull[i-1],CHull[i]);
 res+=dist(CHull.back(),CHull[0]);
 return res; 
}

int main(){
 scanf("%d",&n);
 while(n){
  int bitm,mini=0;
  double extra=0;
  for(int i=0;i<n;i++)
   scanf("%d %d %d %lf",&arr[i].x,&arr[i].y,&v[i],&length[i]),mini+=v[i],extra+=length[i];
  bitm=(1<<n)-1; 
  for(int i=(1<<n)-1;i>=0;i--){
   double len=0;int tot=0;
   proc.clear();
   for(int j=0;j<n;j++)
    if(i&(1<<j))
     tot+=v[j],len+=length[j];
    else
     proc.pb(arr[j]);
   if(tot<mini || (tot==mini && __builtin_popcount(i) < __builtin_popcount(bitm))){
    MonotoneChain();
    double lol=Perimeter();
    if(len+EPS > lol)
     mini=tot,bitm=i,extra=len-lol;
   }    
  }
  if(tc) puts("");
  printf("Forest %d\n",++tc);
  printf("Cut these trees:");
  for(int i=0;i<n;i++)
   if(bitm&(1<<i))
    printf(" %d",i+1);
  puts("");
  printf("Extra wood: %.2lf\n",extra);  
  scanf("%d",&n);
 }
 //puts("ganteng");
 return 0;
}

