#include <cstdio>
using namespace std;

int aktif[1005][1005],valid,r,c,ans;
char x[1005][1005];

void dfs(int rr,int cc){
 if(aktif[rr][cc]==1)
  valid=0;
 else if(aktif[rr][cc]==0){
  aktif[rr][cc]=2;
  if(x[rr][cc]=='S')
   dfs(rr+1,cc);
  if(x[rr][cc]=='W')
   dfs(rr,cc-1);
  if(x[rr][cc]=='N')
   dfs(rr-1,cc);
  if(x[rr][cc]=='E')
   dfs(rr,cc+1);
  aktif[rr][cc]=1;
 }
}

int main(){
 scanf("%d%d",&r,&c);
 getchar();
 for(int a=0;a<r;a++){
  scanf("%s",x[a]);
 }
 for(int a=0;a<r;a++)
  for(int b=0;b<c;b++)
   if(aktif[a][b]==0){
    valid=1;
    dfs(a,b);
    ans+=valid;
   }
 printf("%d\n",ans);
 return 0;
}
