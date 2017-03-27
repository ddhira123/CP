#include <cstdio>
#include <queue>
using namespace std;

int dist[1000005],f,g,s,u,d;
queue<int> q,lang;

int main(){
 scanf("%d%d%d%d%d",&f,&s,&g,&u,&d);
 for(int a=1;a<=f;a++)
  dist[a]=-1;
 dist[s]=0;
 q.push(s);
 lang.push(0);
 while(!q.empty()){
  int node=q.front(),step=lang.front();
  q.pop(); lang.pop();
  if(node+u<=f&&dist[node+u]==-1){
   dist[node+u]=step+1;
   q.push(node+u);
   lang.push(step+1);
  }
  if(node-d>=1&&dist[node-d]==-1){
   dist[node-d]=step+1;
   q.push(node-d);
   lang.push(step+1);
  }
 }
 if(dist[g]==-1)
  printf("use the stairs\n");
 else
  printf("%d\n",dist[g]);
 return 0;
}
