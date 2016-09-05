#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int mask[115];
int n,m,k;
char c[1000005];
char *pch;

inline void proc(){
 for(int i=(1<<n)-1;i>=0;i--){
  bool bisa=1;
  for(int j=m-1;j>=0;j--)
   if((mask[j]&i)==0 || (mask[j]&i)==mask[j]){
    bisa=0;
    break;
   }
  if(bisa){
   printf("Y");
   return;
  } 
 }
 printf("N");
}

int main(){
 scanf("%d",&k);
 while(k--){
  scanf("%d %d",&n,&m);
  getchar();
  for(int i=0;i<m;i++){
   mask[i]=0;
   gets(c);
   pch=strtok(c," ");
   while(pch!=NULL){
    int tmp=atoi(pch)-1;
    mask[i]|=(1<<tmp);
    pch=strtok(NULL," ");
   }
   //printf("%d %d\n",i,mask[i]);
  }
  proc();
 }
// puts("");
 return 0;
}
