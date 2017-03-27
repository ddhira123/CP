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

int arr[55][55];
bool flag[55][55];
vector<int> compress;
string s;
int r,c;
int rs,cs;
vector<pii> interest;

bool BFS(int lo,int hi){
 if(arr[rs][cs] < lo || arr[rs][cs] > hi) return 0;
 for(int i=0;i<r;i++)
  for(int j=0;j<c;j++)
   flag[i][j]=0;
 flag[rs][cs]=1;
 queue<pii> q;
 q.push(mp(rs,cs));
 while(!q.empty()){
  int rr=q.front().fi,cc=q.front().se;
  q.pop();
  for(int i=0;i<8;i++){
   int nr=rr+dx8[i],nc=cc+dy8[i];
   if(nr>=0 && nr<r && nc>=0 && nc<c && !flag[nr][nc] && arr[nr][nc]>=lo && arr[nr][nc]<=hi)
    flag[nr][nc]=1,q.push(mp(nr,nc));
  }
 }
 for(int i=0;i<interest.size();i++){
  int rr=interest[i].fi,cc=interest[i].se;
  if(!flag[rr][cc]) return 0;
 }
 
 return 1;   
}

int main(){
 SYNC;
 cin>>r;
 c=r;
 for(int i=0;i<r;i++){
  cin>>s;
  for(int j=0;j<c;j++)
   if(s[j]=='S') rs=i,cs=j;
   else if(s[j]=='F') interest.pb(mp(i,j));
 }
 for(int i=0;i<r;i++)
  for(int j=0;j<c;j++)
   cin>>arr[i][j],compress.pb(arr[i][j]);
 sort(compress.begin(),compress.end());
 compress.erase(unique(compress.begin(),compress.end()),compress.end());  
 int ans=1000000;
 int le=0;
 for(int i=0;i<compress.size();i++){
  while(compress[i] - compress[le] >= ans) le++;
  while(le<=i && BFS(compress[le],compress[i])) ans=min(ans,compress[i]-compress[le]),le++;
 }
 cout<<ans<<"\n";
 //puts("ganteng");
 return 0;
}
