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
#define INF 1000000000
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

bool cmp(char a,char b){
 if((a-'A')%9==(b-'A')%9)
  return a<b;
 return (a-'A')%9<(b-'A')%9; 
}

vector<char> vow,con;
int tc;

int main(){
 for(char c='A';c<='Z';c++)
  if(c=='A' || c=='E' || c=='I' || c=='U' || c=='O')
   vow.pb(c);
  else
   con.pb(c);
 sort(vow.begin(),vow.end(),cmp);
 sort(con.begin(),con.end(),cmp);
 tc=io();
 for(int t=1;t<=tc;t++){
  int n=io();
  int itv=0,itc=0,ctv=0,ctc=0;
  vector<char> anc,anv;
  printf("Case %d: ",t);
  for(int i=0;i<n;i++)
   if(i&1){
    anc.pb(con[itc]);
    ctc++;
    if(ctc==5)
     ctc=0,itc++;
   }
   else{
    anv.pb(vow[itv]);
    ctv++;
    if(ctv==21)
     ctv=0,itv++;
   }
  sort(anc.begin(),anc.end());
  sort(anv.begin(),anv.end());
  for(int i=0;i<n;i++)
   if(i&1)
    printf("%c",anc[i>>1]);
   else
    printf("%c",anv[i>>1]);  
  puts("");
 }   
 //puts("ganteng");
 return 0;
}

