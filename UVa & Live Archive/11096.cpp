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

struct Point{
 LL x,y;
 
 bool operator ==(Point other) const{
  return x==other.x && y==other.y;
 }
 
 bool operator <(Point other) const{
  return x==other.x ? y<other.y : x<other.x;
 }
};

int n,tc;
vector<Point> v;
double ans;

LL cross(LL dx1,LL dy1,LL dx2,LL dy2){
 return dx1*dy2 - dy1*dx2;
}

bool ccw(Point i,Point j,Point k){
 return cross(i.x-j.x,i.y-j.y,i.x-k.x,i.y-k.y) > 0;
}

void MonotoneChain(vector<Point> &ret){
 ret.clear();
 sort(v.begin(),v.end());
 v.erase(unique(v.begin(),v.end()),v.end());
 vector<Point> up,down;
 Point head=v[0],tail=v.back();
 up.pb(head); down.pb(head);
 for(int i=1;i<v.size();i++){
 
  if(i+1 == v.size() || !ccw(tail,head,v[i])){
   while(up.size() >= 2 && ccw(up[up.size()-2],up[up.size()-1],v[i]))
    up.pop_back();
   up.pb(v[i]); 
  }
  
  if(i+1 == v.size() || ccw(tail,head,v[i])){
   while(down.size() >= 2 && !ccw(down[down.size()-2],down[down.size()-1],v[i]))
    down.pop_back();
   down.pb(v[i]); 
  }
 }
 
 for(int i=0;i<up.size();i++)
  ret.pb(up[i]);
 for(int i=(int)down.size() - 2 ; i>0;i--)
  ret.pb(down[i]);  
 //for(int i=0;i<ret.size();i++)
  //printf("%d %d\n",ret[i].x,ret[i].y);
}

double dist(Point i,Point j){
 return hypot(i.x-j.x,i.y-j.y);
}

double Perimeter(vector<Point> Proc){
 double ret=0;
 for(int i=1;i<Proc.size();i++)
  ret+=dist(Proc[i],Proc[i-1]);//printf("%.2lf\n",ret);
 ret+=dist(Proc[0],Proc[Proc.size()-1]);
 return ret; 
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%lf %d",&ans,&n);
  v.clear();
  for(int i=0;i<n;i++){
   Point tmp;
   scanf("%lld %lld",&tmp.x,&tmp.y);
   v.pb(tmp);
  }
  vector<Point> ConvexHull;
  MonotoneChain(ConvexHull);
  ans=max(ans,Perimeter(ConvexHull));
  printf("%.5lf\n",ans);
 }
 //puts("ganteng");
 return 0;
}

