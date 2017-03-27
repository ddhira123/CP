#include <cstdio>
#include <queue>
#include <algorithm>
#include <map>
#include <string>
#include <cassert>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define INF 1000000000
int res[205][205],ai,li,tc,n,m,yee[205],f,par[205],ans;
char z[105],y[105];
map<string,int> ma;
vector<pii> adj[205];
queue<int> q;
bool visited[205];
pair<int,pii> edge[205];

void Augment(int pos,int Min){
 if(pos==1){
  f=Min;
  return;
 }
 else if(par[pos]!=-1){
  Augment(par[pos],min(Min,res[par[pos]][pos]));
  res[par[pos]][pos]-=f;res[pos][par[pos]]+=f;
 }
}

inline void PlayMax(){
 ans=0;
 while(1){
  f=0;
  for(int i=0;i<=2*n+4;i++)
   visited[i]=0,par[i]=-1;
  q.push(1);
  visited[1]=1;
  while(!q.empty()){
   int pos=q.front();
   q.pop();
   if(pos==2) break;
   /*for(int i=0;i<adj[pos].size();i++){
    int next=adj[pos][i].fi;
    if(!visited[next] && res[pos][next]>0)
     q.push(next),par[next]=pos,visited[next]=1;
   }*/
   for(int i=0;i<=2*n+4;i++)
    if(!visited[i]&&res[pos][i]>0)
     par[i]=pos,visited[i]=1,q.push(i);
  }
  while(!q.empty()) q.pop();
  Augment(2,INF);
  //printf("%d\n",f);
  if(f==0) break;
  ans+=f;
 }
}

int finds(int x){
 return x==par[x] ? x : par[x]=finds(par[x]);
}

int main(){
 scanf("%d",&tc);
 for(int t=1;t<=tc;t++){
 ma.clear();
 scanf("%d %d",&n,&m);
 ma["ronnys_work"]=0;
 ma["ronnys_house"]=1;
 for(int i=2;i<=n+1;i++){
   scanf("%s %d %d",z,&ai,&li);
   //puts("ayaz");
   int cost=0;
   for(int j=1;j<=ai;j++)
    par[j]=j;
   for(int j=0;j<li;j++)
    scanf("%d %d %d",&edge[j].se.fi,&edge[j].se.se,&edge[j].fi);
   sort(edge,edge+li);
   for(int j=li-1;j>=0;j--){
    int lol1=edge[j].se.fi,lol2=edge[j].se.se;
    //printf("%d %d\n",lol1,lol2);
    lol1=finds(lol1),lol2=finds(lol2);
    if(lol1!=lol2){
     //puts("DEBUG");
     par[lol1]=lol2;
     if(finds(1) == finds(ai)){
      cost=edge[j].fi;
      break;
     }
    }
   }  
   //printf("%d\n",cost);
   //assert(cost > 0);
   yee[i]=cost;
   ma[(string)z]=i;
  }
  for(int i=0;i<=2*n+4;i++){
   adj[i].clear();
   for(int j=0;j<=2*n+4;j++)
    res[i][j]=0;
  }
  for(int i=0;i<=n+1;i++){
   adj[2*i].push_back(mp(2*i+1,0));
   adj[2*i+1].push_back(mp(2*i,0));
   res[2*i][2*i+1]=yee[i];
   //res[2*i+1][2*i]=yee[i];
  }
  while(m--){
   int hm;
   //printf("%d\n",m);
   scanf("%s %s %d",y,z,&hm);
   int yy,zz;
   yy=ma[(string)y];
   zz=ma[(string)z];
   res[2*yy+1][2*zz]+=hm;
   //res[2*zz][2*yy+1]+=hm;
   adj[2*yy+1].push_back(mp(2*zz,0));
   adj[2*zz].push_back(mp(2*yy+1,0));
   //adj[2*zz+1].push_back(mp(2*yy,0));
   //adj[2*yy].push_back(mp(2*zz+1,0));
  }
  PlayMax();
  printf("Scenario #%d: %d\n",t,ans);
 }
 return 0;
}