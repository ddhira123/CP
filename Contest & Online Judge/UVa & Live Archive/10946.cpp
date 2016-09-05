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

typedef pair<int,char> pic;

bool cmp(pic i,pic j){
 return i.fi==j.fi ? i.se<j.se : i.fi>j.fi;
}

vector<pic> v;
int tc;
int x,y;
string arr[55];

inline void BFS(int rs,int cs){
 int cnt=0;
 char pivot=arr[rs][cs];
 arr[rs][cs]='.';
 queue<pii> q;
 q.push(mp(rs,cs));
 while(!q.empty()){
  int rr=q.front().fi,cc=q.front().se;
  q.pop();
  cnt++;
  for(int i=0;i<4;i++){
   int nr=rr+dx4[i],nc=cc+dy4[i];
   if(nr>=0 && nc>=0 && nr<x && nc<y && arr[nr][nc]==pivot)
    arr[nr][nc]='.',q.push(mp(nr,nc));
  }
 }
 v.pb(mp(cnt,pivot));
}

int main(){
 SYNC;
 cin>>x>>y;
 while(x|y){
  v.clear();
  for(int i=0;i<x;i++)
   cin>>arr[i];
  for(int i=0;i<x;i++)
   for(int j=0;j<y;j++)
    if(arr[i][j]!='.') BFS(i,j);
  sort(v.begin(),v.end(),cmp);
  cout<<"Problem "<<++tc<<":\n";
  for(int i=0;i<v.size();i++)
   cout<<v[i].se<<" "<<v[i].fi<<"\n";   
  cin>>x>>y;
 }
 //puts("ganteng");
 return 0;
}

