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
#define g getchar_unlocked
#define INF 2000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL
#define DEBUG puts("DEBUG")


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

int arr[15][105],dp[15][105],next[15][105];
int n,m;
pii tmp[3];

bool cmp(pii a,pii b){
 if(a.fi==b.fi)
  return a.se<b.se;
 return a.fi<b.fi; 
}

inline void PlayDP(){
 for(int i=0;i<n;i++)
  dp[i][m-1]=arr[i][m-1];
 for(int i=m-2;i>=0;i--)
  for(int j=0;j<n;j++){
   for(int k=-1;k<=1;k++)
    tmp[k+1]=mp(dp[(j+k+n)%n][i+1],(j+k+n)%n);
   sort(tmp,tmp+3,cmp); 
   next[j][i]=tmp[0].se;
   dp[j][i]=arr[j][i]+tmp[0].fi;
   //printf("ROW %d COL %d ARR %d DP %d\n",j,i,arr[j][i],dp[j][i]);
  } 
}

inline void Print(){
 int ans=INF;
 int pos;
 for(int i=0;i<n;i++)
  if(dp[i][0]<ans)
   ans=dp[i][0],pos=i;
 printf("%d",pos+1);
 pos=next[pos][0];
 for(int i=1;i<m;i++)
  printf(" %d",pos+1),pos=next[pos][i];
 printf("\n%d\n",ans);   
}

int main(){
 while(scanf("%d %d",&n,&m)==2){
  for(int i=0;i<n;i++)
   for(int j=0;j<m;j++)
    scanf("%d",&arr[i][j]);
  PlayDP();
  Print();  
 }
 //puts("ganteng");
 return 0;
}

