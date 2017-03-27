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

int prefix[26][501][501];
char s[505][505];
int r,c,n;
pii arr[505];

int main(){
 scanf("%d %d",&r,&c);
 for(int i=1;i<=r;i++){
  scanf("%s",s[i]); 
  for(int j=1;j<=c;j++)
   for(int k=0;k<26;k++){
    prefix[k][i][j]=prefix[k][i][j-1] + prefix[k][i-1][j] - prefix[k][i-1][j-1];
    if(s[i][j-1] - 'a' == k)
     prefix[k][i][j]++;
   }
 }
 int rmin,cmin,rmaks,cmaks;
 rmin=cmin=INF;
 rmaks=cmaks=-INF;
 scanf("%d",&n);
 pii pivot=mp(INF,INF);
 for(int i=0;i<n;i++){
  scanf("%d %d",&arr[i].se,&arr[i].fi);
  arr[i].fi++;
  arr[i].se++;
  rmin=min(rmin,arr[i].fi);
  rmaks=max(rmaks,arr[i].fi);
  cmin=min(cmin,arr[i].se);
  cmaks=max(cmaks,arr[i].se);
  if(arr[i].se < pivot.se || (arr[i].se == pivot.se && arr[i].fi < pivot.fi))
   pivot=arr[i];
 }
 rmaks-=(rmin-1);
 cmaks-=(cmin-1);
 for(int i=0;i<n;i++)
  arr[i].fi-=(rmin-1),arr[i].se-=(cmin-1);
 pivot.fi-=(rmin-1);
 pivot.se-=(cmin-1);
 int ans=0;
 //printf("%d %d\n",rmaks,cmaks);
 for(int i=0;i + rmaks  <= r + 1 ; i++)
  for(int j=0; j + cmaks  <= c + 1; j++){
   int tot=0;
   int cmp=0;
   char lol=s[i + pivot.fi][j + pivot.se - 1]-'a';
   for(int k=0;k<n;k++){
    int l=k+1;
    if(l==n) l=0;
    int r1=arr[l].fi;
    int r2=arr[k].fi;
    int c1=arr[l].se;
    int c2=arr[k].se;
    if(c1==c2){
     if(r1 < r2){
      tot-=prefix[lol][r2 + i - 1][c2 + j - 1] - prefix[lol][r1 + i - 1][c1 + j -1];
      cmp-=c2*(r2-r1);
     } 
     else{
      tot+=prefix[lol][r1 + i - 1][c1 + j - 1] - prefix[lol][r2 + i - 1][c2 + j -1];
      cmp+=c2*(r1-r2);
     } 
    }
    //printf("%d %d -> %d %d\n",i,j,tot,cmp);
   }
   //printf("%d %d -> %d %d\n",i,j,tot,cmp);
   if(cmp==tot) ans++;
  }   
  printf("%d\n",ans);
 //puts("ganteng");
 return 0;
}
