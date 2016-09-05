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
#define MOD 1000000007LL

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

int LDS[2005],arr[2005],LIS[2005];
int n,tc;

int main(){
 tc=io();
 while(tc--){
  n=io();
  int ans=0;
  for(int i=0;i<n;i++)
   arr[i]=io();
  for(int i=n-1;i>=0;i--){
   LDS[i]=0;
   LIS[i]=0;
   for(int j=n-1;j>i;j--)
    if(arr[j]>arr[i])
     LDS[i]=max(LDS[i],LDS[j]);
    else
     LIS[i]=max(LIS[i],LIS[j]); 
   LDS[i]++;
   LIS[i]++;
   //printf("NOW %d LIS %d LDS %d\n",i,LDS[i],LIS[i]);
   ans=max(ans,LDS[i] + LIS[i] - 1);  
  } 
  printf("%d\n",ans); 
 }
 //puts("ganteng");
 return 0;
}

