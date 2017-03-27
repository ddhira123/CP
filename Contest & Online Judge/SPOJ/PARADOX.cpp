#include <cstdio>
#include <vector>
using namespace std;


int n,a,b,tem[105],root[105];
vector<int> v;
bool ket[105],nil[105],aktif[105],yee;
char dum[5];

void dfs(int x,bool y){
 if(aktif[x]&&(y!=nil[x]))
  yee=false;
 else if(!aktif[x]){
  aktif[x]=1;
  nil[x]=y;
  v.push_back(x);
  if(y==1)
   dfs(tem[x],ket[x]);
  else
   dfs(tem[x],!ket[x]);
 }
}
int main(){
 scanf("%d",&n);
 while(n){
 for(a=1;a<=n;a++)
  root[a]=1;
 for(a=1;a<=n;a++){
  scanf("%d %s",&b,dum);
  tem[a]=b;
  aktif[a]=0;
  root[b]=0;
  if(dum[0]=='f')
   ket[a]=0;
  else
   ket[a]=1;
 }
 bool ans=1;
 for(a=1;a<=n&&ans;a++)
  if(root[a]){
   bool yoo=0;
   for(b=0;b<=1&&!yoo;b++){
    yee=1;
    dfs(a,b);
    if(yee){
     yoo=1;
     while(!v.empty())
      v.pop_back();
    }
    else
     while(!v.empty()){
      aktif[v.back()]=0;
      v.pop_back();
     }
   }
   ans&=yoo;
  }
 for(a=1;a<=n&&ans;a++)
  if(!aktif[a]){
   bool yoo=0;
   for(b=0;b<=1&&!yoo;b++){
    yee=1;
    dfs(a,b);
    if(yee){
     yoo=1;
     while(!v.empty())
      v.pop_back();
    }
    else
     while(!v.empty()){
      aktif[v.back()]=0;
      v.pop_back();
     }
   }
   ans&=yoo;
  }
  if(ans)
   printf("NOT PARADOX\n");
  else
   printf("PARADOX\n");
  scanf("%d",&n);
 }
 return 0;
}
