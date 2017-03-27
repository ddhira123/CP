#include <cstdio>
using namespace std;

int tot[10],tc,n;
char x[50];

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(int i=0;i<10;i++)
   tot[i]=0;
  scanf("%s",x);
  for(int i=0;i<38;i++)
   if(x[i]=='T'){
    if(x[i+1]=='T'){
     if(x[i+2]=='T')
      tot[0]++;
     else
      tot[1]++;
    }
    else{
     if(x[i+2]=='T')
      tot[2]++;
     else
      tot[3]++;
    }
   }
   else{
    if(x[i+1]=='T'){
     if(x[i+2]=='T')
      tot[4]++;
     else
      tot[5]++;
    }
    else{
     if(x[i+2]=='T')
      tot[6]++;
     else
      tot[7]++;
    }
   }
  printf("%d %d %d %d %d %d %d %d %d\n",n,tot[0],tot[1],tot[2],tot[3],tot[4],tot[5],tot[6],tot[7]);
 }
 return 0;
}