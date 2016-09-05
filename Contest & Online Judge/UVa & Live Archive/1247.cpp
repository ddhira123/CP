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
#define N 26
int use[30][30],dist[30][30],par[30][30];
char x,y;
int n,m,a;

inline void reset(){
 for(int i=0;i<N;i++)
  for(int j=0;j<N;j++)
   use[i][j]=dist[i][j]=INF,par[i][j]=i;  
}

inline void War(){
 for(int i=0;i<N;i++)
  for(int j=0;j<N;j++)
   for(int k=0;k<N;k++)
    if(dist[j][k]>dist[j][i]+dist[i][k] || (dist[j][k]==dist[j][i]+dist[i][k] && use[j][k]>use[j][i]+use[i][k])){
     dist[j][k]=dist[j][i]+dist[i][k];
     par[j][k]=par[i][k];
     use[j][k]=use[j][i]+use[i][k];
    }
}

void Print(int s,int t){
 //cout<<s<<" "<<t<<"\n";
 if(s!=t){
  Print(s,par[s][t]);
  cout<<" ";
 }
 cout<<(char)(t+'A');
}

int main(){
 cin.tie(0);
 reset();
 cin>>n>>m;
 while(m--){
  cin>>x>>y>>a;
  x-='A';
  y-='A';
  dist[x][y]=min(dist[x][y],a);
  dist[y][x]=min(dist[y][x],a);
  use[x][y]=1;
  use[y][x]=1;
 }
 for(int i=0;i<N;i++)
  dist[i][i]=0,use[i][i]=0;
 War();
 int q;
 cin>>q;
 while(q--){
  cin>>x>>y;
  Print(x-'A',y-'A');
  cout<<"\n";
 } 
 //puts("ganteng");
 return 0;
}

