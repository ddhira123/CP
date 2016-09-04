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
#define INF 2000000000
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

int dist[4001][4001];
int arr[2001][201],prefc[2001][201],prefr[2001];
int tmp[4001];
int r,c;

inline void Preprocess(){
 set<pii> s;
 for(int i=1;i<=2*r;i++){
  for(int j=1;j<=2*r;j++)
   s.insert(mp(INF,j)),tmp[j]=INF;
  tmp[i]=0;
  //printf("NOW %d\n",i);
  s.erase(mp(INF,i));
  s.insert(mp(0,i));
  while(!s.empty()){
   pii aa=*s.begin();
   int cost=aa.fi,pos=aa.se;
   s.erase(s.begin());
    //printf("%d -> %d\n",pos,cost);
    int rr=(pos+1)>>1;
    int cc=(pos&1 ? 1 : c);
    if(rr>1 && arr[rr-1][cc]+cost < tmp[pos-2])
     s.erase(mp(tmp[pos-2],pos-2)),tmp[2*rr-2 - (cc!=c)]=arr[rr-1][cc]+cost,s.insert(mp((arr[rr-1][cc]+cost),pos-2));
    if(rr<r && arr[rr+1][cc]+cost < tmp[pos+2])
     s.erase(mp(tmp[pos+2],pos+2)),tmp[2*rr+2 - (cc!=c)]=arr[rr+1][cc]+cost,s.insert(mp((arr[rr+1][cc]+cost),pos+2));
    if(pos&1) pos++;
    else pos--;
    if(cost + prefc[rr][c] - arr[rr][cc] < tmp[pos])
     s.erase(mp(tmp[pos],pos)),tmp[pos]=cost+prefc[rr][c]-arr[rr][cc],s.insert(mp((cost+prefc[rr][c]-arr[rr][cc]),pos));      
   
  }
   for(int j=1;j<=2*r;j++)
    dist[i][j]=tmp[j];
 }
}

int main(){
 r=io(),c=io();
 for(int i=1;i<=r;i++)
  for(int j=1;j<=c;j++)
   arr[i][j]=io(),prefc[i][j]=arr[i][j]+prefc[i][j-1];
 int k,rr,cc;
 if(c>1){
  Preprocess();
 }   
 else
  for(int i=1;i<=r;i++)
   prefr[i]=prefr[i-1]+arr[i][1];
 rr=1;
 cc=1;
 LL ans=arr[1][1];
 k=io();
 while(k--){
  int rk=io(),ck=io();
  int best=INF;
  if(c==1)
   best=prefr[max(rr,rk)-1]-prefr[min(rr,rk)-1];
  else{
   best=min(best,prefc[rr][cc-1] + dist[2*rr-1][2*rk-1] + prefc[rk][ck] - arr[rk][1]);
   best=min(best,prefc[rr][cc-1] + dist[2*rr-1][2*rk] + prefc[rk][c-1] - prefc[rk][ck-1]);
   best=min(best,prefc[rr][c] - prefc[rr][cc] + dist[2*rr][2*rk-1] + prefc[rk][ck] - arr[rk][1]);
   best=min(best,prefc[rr][c] - prefc[rr][cc] + dist[2*rr][2*rk] + prefc[rk][c-1] - prefc[rk][ck-1]);
  }
  ans+=(LL)best;
  rr=rk;
  cc=ck; 
  //printf("%d\n",best);
 }  
 printf("%lld\n",ans);
 //puts("ganteng");
 return 0;
}

