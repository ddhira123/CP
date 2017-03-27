#include <cstdio>
#include <cstring>
using namespace std;

char x[120005],op[120005];
int siz,tc;

int main(){
 scanf("%d",&tc);
 for(int t=1;t<=tc;t++){
  siz=0;
  scanf("%s",x);
  int len=strlen(x);
  for(int i=0;i<len;i++)
   if(siz>=2 && op[siz-2]=='1' && op[siz-1]=='0' && x[i]=='0')
    siz-=2;
   else
    op[siz++]=x[i];
  printf("Case %d: ",t);
  if(siz==0) puts("yes");
  else       puts("no");
 }
 return 0;
}