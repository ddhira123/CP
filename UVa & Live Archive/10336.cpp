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

int tc;
int h,w;
string v[3005];
int ctr[30];
pair<int,char> arr[30];

void BFS(int rs,int cs){
 char pivot=v[rs][cs];
 ctr[pivot-'a']++;
 queue<pii> q;
 v[rs][cs]=' ';
 q.push(mp(rs,cs));
 while(!q.empty()){
  int rr=q.front().fi,cc=q.front().se;
  q.pop();
  for(int i=0;i<4;i++){
   int nr=rr+dx4[i],nc=cc+dy4[i];
   if(nr>=0 && nc>=0 && nr<h && nc<w && v[nr][nc]==pivot)
    v[nr][nc]=' ',q.push(mp(nr,nc));
  }
 }
}

bool cmp(pair<int,char> i,pair<int,char> j){
 if(i.fi==j.fi) return i.se < j.se;
 return i.fi>j.fi;
}

int main(){
 SYNC;
 cin>>tc;
 for(int t=1;t<=tc;t++){
  for(int i=0;i<26;i++) 
   ctr[i]=0;
  cin>>h>>w;
  for(int i=0;i<h;i++)
   cin>>v[i];
  for(int i=0;i<h;i++)
   for(int j=0;j<w;j++)
    if(v[i][j]!=' ') BFS(i,j);
  for(int i=0;i<26;i++)
   arr[i]=mp(ctr[i],i+'a'); 
  sort(arr,arr+26,cmp);
  cout<<"World #"<<t<<"\n";
  for(int i=0;i<26;i++)
   if(arr[i].fi)
    cout<<arr[i].se<<": "<<arr[i].fi<<"\n";    
 }
 //puts("ganteng");
 return 0;
}

