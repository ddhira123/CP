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

inline int add(int &x,int y){
 x+=y;
 if(x==10) x=0;
 else if(x==-1) x=9;
}

int arr[15][15];
char s[15];
int a,b,n,tc,q;


int main(){
 scanf("%d",&tc);
 for(int t=1;t<=tc;t++){
  scanf("%d",&n);
  for(int i=0;i<n;i++){
   scanf("%s",s);
   for(int j=0;j<n;j++)
    arr[i][j]=s[j]-'0';
  }
  scanf("%d",&q);
  while(q--){
   scanf("%s",s);
   if(s[0]=='i'){
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
      add(arr[i][j],1);
   }
   else if(s[0]=='d'){
    for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
      add(arr[i][j],-1);
   }
   else if(s[0]=='t'){
    for(int i=0;i<n;i++)
     for(int j=i+1;j<n;j++)
      swap(arr[i][j],arr[j][i]);
   }
   else{
    scanf("%d %d",&a,&b);
    a--,b--;
    if(s[0]=='r')
     for(int i=0;i<n;i++)
      swap(arr[a][i],arr[b][i]);
    else
     for(int i=0;i<n;i++)
      swap(arr[i][a],arr[i][b]);  
   }
  }
  printf("Case #%d\n",t);
  for(int i=0;i<n;i++){
   for(int j=0;j<n;j++)
    printf("%d",arr[i][j]);
   puts(""); 
  }  
  puts("");
 }
 //puts("ganteng");
 return 0;
}

