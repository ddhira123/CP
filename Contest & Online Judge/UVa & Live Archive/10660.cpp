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

int n;
int sum[30];
int tc;
int x,y,z;
int tmp[10],ans[10];

int main(){
 scanf("%d",&tc);
 while(tc--){

  scanf("%d",&n);
  for(int i=0;i<25;i++) sum[i]=0;
  while(n--){
   scanf("%d %d %d",&x,&y,&z);
   sum[x*5+y]+=z;
  }
  int mini=INF;
  for(tmp[0]=0;tmp[0]<25;tmp[0]++)
   for(tmp[1]=tmp[0]+1;tmp[1]<25;tmp[1]++)
    for(tmp[2]=tmp[1]+1;tmp[2]<25;tmp[2]++)
     for(tmp[3]=tmp[2]+1;tmp[3]<25;tmp[3]++)
      for(tmp[4]=tmp[3]+1;tmp[4]<25;tmp[4]++){
       //assert(tmp[0]!=tmp[1] && tmp[0]!=tmp[2] && tmp[0]!=tmp[3] && tmp[0]!=tmp[4]);
       int tot=0;
       for(int i=0;i<25;i++)
        if(sum[i]){
         int mindiff=INF;
         for(int j=0;j<5;j++)
          mindiff=min(mindiff,abs(i/5 - tmp[j]/5) + abs((i%5) - (tmp[j]%5)));
         tot+=sum[i]*mindiff; 
        } 
       if(tot<mini){
        mini=tot;
        for(int i=0;i<5;i++)
         ans[i]=tmp[i];
        }  
      }
   printf("%d %d %d %d %d\n",ans[0],ans[1],ans[2],ans[3],ans[4]);            
 } 
 //puts("ganteng");
 return 0;
}

