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

string arr[2005];
int n;
int dist[2005];
int len[2005];
string source,destination;
vector<pii> adj[2005];
//dummy source 0
//dummy sink 1

inline void PlayDijkstra(){
 dist[0]=0;
 priority_queue<pii> pq;
 pq.push(mp(0,0));
 while(!pq.empty()){
  int dis=-pq.top().fi,now=pq.top().se;
  pq.pop();
  if(now==1){
   printf("%d\n",dis);
   return;
  }
  else if(dis==dist[now])
   for(int i=0;i<adj[now].size();i++){
    int nxt=adj[now][i].fi,ndis=dis+adj[now][i].se;
    if(dist[nxt] > ndis)
     dist[nxt]=ndis,pq.push(mp(-ndis,nxt));
   }
 }
   puts("impossivel"); 
 //for(int i=0;i<n+2;i++)
  //printf("POS %d DISTANCE %d\n",i,dist[i]);
}

vector<int> lis[5005]; //idx
map<string,int> ms;
string yee,yoo;

int main(){
 SYNC;
 cin>>n;
 while(n){
  ms.clear();
  cin>>source>>destination;
  adj[0].clear();adj[1].clear();
  dist[0]=dist[1]=INF;
  lis[0].clear(),lis[1].clear();
  int sz=2;
  ms[source]=0;
  ms[destination]=1;
  for(int i=0;i<n;i++){
   cin>>yee>>yoo>>arr[i];
   dist[i+2]=INF;
   adj[i+2].clear();
   len[i]=arr[i].length();
   if(ms.find(yee)==ms.end())
    lis[sz].clear(),ms[yee]=sz++;
   if(ms.find(yoo)==ms.end()) 
    lis[sz].clear(),ms[yoo]=sz++;
   int nxt[2]={ms[yee],ms[yoo]};
   for(int j=0;j<2;j++)
    for(int k=0;k<lis[nxt[j]].size();k++){
     int idx=lis[nxt[j]][k];
     if(arr[idx][0]!=arr[i][0]){
      adj[idx+2].pb(mp(i+2,len[i]));
      adj[i+2].pb(mp(idx+2,len[idx]));
     } 
    }
   for(int j=0;j<2;j++)
    lis[nxt[j]].pb(i);
   if(yee==source || yoo==source)
    adj[0].pb(mp(i+2,len[i]));
   if(yee==destination || yoo==destination)
    adj[i+2].pb(mp(1,0));   
  }
  PlayDijkstra();
  cin>>n;
 }
 //puts("ganteng");
 return 0;
}

