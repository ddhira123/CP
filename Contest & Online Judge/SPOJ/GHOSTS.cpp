#include <cstdio>
using namespace std;

bool adj[1005][1005];
int k,m,a,b,sum[1005];


#define g getchar_unlocked
inline int io(){
register char c;
while(1){
c=g();
if((c^32) && (c^10)) break;
}
register int res=c-'0';
while(1){
c=g();
if(!(c^32) || !(c^10))
return res;
res=(res<<3)+(res<<1)+(c-'0');
}
}

int main(){
 k=io();
 for(int i=1;i<=k;i++)
  adj[i][i]=1;
 m=io();
 while(m--){
  a=io();b=io();
  if(adj[b][a])
   printf("%d %d\n",a,b);
  else if(!adj[a][b]){
   for(int i=1;i<=k;i++)
    if(adj[i][a]&&!adj[i][b])
    for(int j=1;j<=k;j++)
     adj[i][j]|=adj[b][j];
   adj[a][b]=1;
  }
 }
 printf("0 0\n");
 return 0;
}

