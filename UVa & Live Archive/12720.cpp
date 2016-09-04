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

typedef pair<int,int> pii;
typedef long long LL;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SYNC ios_base::sync_with_stdio(false)
#define g getchar_unlocked
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007

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
 if(x>=MOD) x-=MOD;
}

int l,r;
int po[100005],ans;
int len;

char c[100005];
int tc;

int main(){
 scanf("%d",&tc);
 po[0]=1;
 for(int i=1;i<=100000;i++)
  po[i]=po[i-1],add(po[i],po[i]);
 for(int t=1;t<=tc;t++){
  scanf("%s",c);
  len=strlen(c);
  ans=0;
  r=len>>1;
  l=r-1;
  for(int i=0;i<len;i++){
   if(l+1 > len-r){
    if(c[l]=='1')
     add(ans,po[len-i-1]);
    l--; 
   }
   else if(l+1 < len-r){
    if(c[r]=='1')
     add(ans,po[len-i-1]);
    r++; 
   }
   else if(c[l]=='1')
    add(ans,po[len-i-1]),l--;
   else if(c[r]=='1')
    add(ans,po[len-i-1]),r++;
   else
    l--;   
  }
  //printf("%d %d\n",l,r);
  printf("Case #%d: %d\n",t,ans);
 }
 //puts("ganteng");
 return 0;
}

