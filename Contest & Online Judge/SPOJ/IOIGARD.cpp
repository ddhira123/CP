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

int arr[255][255];
int prefix[255][255];
int ans[255];
int n,k,x,y,r,c;
int ret=INF;

inline void Row_Based(){
 for(int i=1;i<=r;i++)
  for(int j=1;j<=c;j++)
   prefix[i][j]=prefix[i-1][j]+arr[i][j];
 ans[0]=INF;
 for(int i=1;i<=r;i++){
  ans[i]=ans[i-1];
  for(int j=1;j<=i;j++){
   int sum=0,le=1;
   for(int rig=1;rig<=c;rig++){
    sum+=prefix[i][rig]-prefix[j-1][rig];
    while(sum-(prefix[i][le]-prefix[j-1][le]) >= k) sum-=(prefix[i][le]-prefix[j-1][le]),le++;
    
    if(sum==k){
     //cout<<"UP "<<j<<" DOWN "<<i<<" LEFT "<<le<<" RIGHT "<<rig;
     int cost=2*(rig-le+1 + i-j+1);
     //cout<<" COST "<<cost<<"\n";
     ans[i]=min(ans[i],cost);
     ret=min(ret,cost+ans[j-1]);
    }
   }
  }
 }  
}

inline void Col_Based(){
 for(int i=1;i<=c;i++)
  for(int j=1;j<=r;j++)
   prefix[j][i]=prefix[j][i-1]+arr[j][i];
 ans[0]=INF;
 for(int i=1;i<=c;i++){
  ans[i]=ans[i-1];
  for(int j=1;j<=i;j++){
   int sum=0,up=1;
   for(int down=1;down<=r;down++){
    sum+=prefix[down][i]-prefix[down][j-1];
    while(sum-(prefix[up][i]-prefix[up][j-1]) >= k) sum-=(prefix[up][i]-prefix[up][j-1]),up++;
    
    if(sum==k){
     int cost=2*(down-up+1 + i-j+1);
     ans[i]=min(ans[i],cost);
     ret=min(ret,cost+ans[j-1]);
    }
   }
  }
 }  
}

int main(){
 r=io(),c=io();;
 n=io(),k=io();
 while(n--){
  x=io(),y=io();
  arr[x][y]++;
 }
 Row_Based();
 Col_Based();
 if(ret==INF) puts("NO");
 else         printf("%d\n",ret);
 //puts("ganteng");
 return 0;
}
