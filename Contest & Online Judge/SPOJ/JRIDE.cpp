#include <cstdio>
using namespace std;

int anski,anska,ki,maks,sum,a,b,tc,i,n;

int main(){
 scanf("%d",&tc);
 for(i=1;i<=tc;i++){
  maks=sum=0;
  ki=anski=anska=1;
  scanf("%d",&n);
  for(a=1;a<n;a++){
   scanf("%d",&b);
   sum+=b;
   if(sum>maks){
    anski=ki;
    anska=a+1;
    maks=sum;
   }
   else if(sum==maks){
    if(a+1-ki>anska-anski){
     anska=a+1;
     anski=ki;
    }
   }
   else if(sum<0){
    sum=0;
    ki=a+1;
   }
  }
 if(maks>0)
  printf("The nicest part of route %d is between stops %d and %d\n",i,anski,anska);
 else
  printf("Route %d has no nice parts\n",i);
 }
 return 0;
}
