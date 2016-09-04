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

int dist[51][51][51];
int n;
char arr[51][51];

struct state{
 int p1,p2,p3;
 state(int x,int y,int z){
  p1=x,p2=y,p3=z;
 }
};

void solve(int a,int b,int c){
 for(int i=1;i<=n;i++)
  for(int j=1;j<=n;j++)
   for(int k=1;k<=n;k++)
    dist[i][j][k]=-1;
 dist[a][b][c]=0;
 queue<state> q;
 q.push(state(a,b,c));
 while(!q.empty()){
  a=q.front().p1, b=q.front().p2, c=q.front().p3;
  if(a==b && b==c){
   cout << dist[a][b][c] << "\n";
   return;
  }
  q.pop();
  for(int i=1;i<=n;i++)
   if(arr[a][i]==arr[b][c] && dist[i][b][c]==-1)
    dist[i][b][c]=dist[a][b][c] + 1,q.push(state(i,b,c));
  for(int i=1;i<=n;i++)
   if(arr[b][i]==arr[a][c] && dist[a][i][c]==-1)
    dist[a][i][c]=dist[a][b][c] + 1,q.push(state(a,i,c));
  for(int i=1;i<=n;i++)
   if(arr[c][i]==arr[a][b] && dist[a][b][i]==-1)
    dist[a][b][i]=dist[a][b][c] + 1,q.push(state(a,b,i));  
 }
 cout << "impossible\n";
}

int main(){
 SYNC;
 cin >> n;
 while(n){
  int a,b,c;
  cin >> a >> b >> c;
  for(int i=1;i<=n;i++)
   for(int j=1;j<=n;j++)
    cin >> arr[i][j];
  solve(a,b,c);  
  cin >> n;
 }
 //puts("ganteng");
 return 0;
}

