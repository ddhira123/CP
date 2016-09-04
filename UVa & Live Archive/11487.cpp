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

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SYNC ios_base::sync_with_stdio(false)
#define g getchar_unlocked
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 20437
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

inline void add(int &x,int y){
 x+=y;
 if(x>=MOD) x-=MOD;
}

int dist[27][11][11],dp[27][11][11];
pii st[27];
queue<pii> q;
char s[11][11];
int n,tc;

inline void Precompute(){
 for(int i=0;i<26;i++)
  st[i]=mp(-1,-1);
 for(int i=0;i<n;i++)
  for(int j=0;j<n;j++){
   for(int k=0;k<26;k++)
    dist[k][i][j]=-1;
   if(s[i][j]>='A' && s[i][j]<='Z')
    st[s[i][j]-'A']=mp(i,j); 
  }
}

inline void PlayDP(){
 Precompute();
 int val=1;
 int totdist=0;
 bool valid=1;
 for(int i=0;i<25;i++){
  if(st[i+1].fi==-1) break;
  q.push(st[i]);
  dp[i][st[i].fi][st[i].se]=val;
  dist[i][st[i].fi][st[i].se]=0;
  while(!q.empty()){
   int r=q.front().fi,c=q.front().se;
   //printf("POS %d %d %d DIST %d\n",i,r,c,dist[i][r][c]);
   q.pop();
   for(int j=0;j<4;j++){
    int nr=r+dx4[j];
    int nc=c+dy4[j];
    if(nr>=0 && nr<n && nc>=0 && nc<n && (s[nr][nc]=='.' || (s[nr][nc]>='A' && s[nr][nc]<='A'+i+1) ) ){
     if(dist[i][nr][nc]==-1)
      dist[i][nr][nc]=dist[i][r][c]+1,dp[i][nr][nc]=dp[i][r][c],q.push(mp(nr,nc));
     else if(dist[i][r][c]+1==dist[i][nr][nc])
      add(dp[i][nr][nc],dp[i][r][c]); 
    }
   }
  }
  if(dist[i][st[i+1].fi][st[i+1].se]==-1){
   valid=0;
   break;
  }
  else{
   totdist+=dist[i][st[i+1].fi][st[i+1].se];
   val=dp[i][st[i+1].fi][st[i+1].se];
  }
 }
 if(!valid)
  puts("Impossible");
 else
  printf("%d %d\n",totdist,val); 
}

int main(){
 scanf("%d",&n);
 while(n){
  for(int i=0;i<n;i++)
   scanf("%s",s[i]);
  printf("Case %d: ",++tc);
  PlayDP(); 
  scanf("%d",&n);
 }
 //puts("ganteng");
 return 0;
}

