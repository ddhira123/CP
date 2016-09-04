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

pair<string,pii> arr[15];
int tc;
int ans[15];
bool flag[15];

int main(){
 SYNC;
 cin>>tc;
 for(int t=1;t<=tc;t++){
  for(int i=0;i<10;i++)
   cin>>arr[i].fi>>arr[i].se.fi>>arr[i].se.se,flag[i]=0;
  sort(arr,arr+10);
  int maka=-1,makd=-1;
  for(int i=0;i<10;i++)
   for(int j=i+1;j<10;j++)
    for(int k=j+1;k<10;k++)
     for(int l=k+1;l<10;l++)
      for(int m=l+1;m<10;m++){
       int suma=arr[i].se.fi + arr[j].se.fi + arr[k].se.fi + arr[l].se.fi + arr[m].se.fi;
       int sumd=0;
       for(int n=0;n<10;n++)
        if(n!=i && n!=j && n!=k && n!=l && n!=m)
         sumd+=arr[n].se.se;
       if(suma > maka || (suma == maka && sumd > makd)){
        maka=suma;
        makd=sumd;
        ans[0]=i;
        ans[1]=j;
        ans[2]=k;
        ans[3]=l;
        ans[4]=m;
       }       
      }
  for(int i=0;i<5;i++) flag[ans[i]]=1;
  cout<<"Case "<<t<<":\n";
  for(int i=0;i<2;i++){
   cout<<"("<<arr[ans[0]].fi<<", "<<arr[ans[1]].fi<<", "<<arr[ans[2]].fi<<", "<<arr[ans[3]].fi<<", "<<arr[ans[4]].fi<<")\n";
   int it=0;
   for(int j=0;j<10;j++) 
     if(!flag[j])
      ans[it++]=j;
  }    
 }
 //puts("ganteng");
 return 0;
}

