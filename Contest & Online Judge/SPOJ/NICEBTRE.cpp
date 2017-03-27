#include <cstdio>
#include <algorithm>
using namespace std;

char x[10005];
int tc,ans,pos;

void traverse(int depth){
 ans=max(ans,depth);
 if(x[pos]=='n')
  for(int i=0;i<2;i++){
   pos++;
   traverse(depth+1);
  }
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%s",x);
  pos=ans=0;
  traverse(0);
  printf("%d\n",ans);
 }
 return 0;
}