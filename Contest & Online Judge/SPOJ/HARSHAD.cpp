#include <cstdio>
using namespace std;

bool prime[1000005],dev[1000005];
int prefix[1000005],a,b,tc;

int d(int n){
 int res=0;
 while(n>0){
  res+=n%10;
  n/=10;
 }
 return res;
}

int main(){
 for(a=1;a<=1000000;a++){
  int jum=a+d(a);
  if(jum<=1000000)
   dev[jum]=1;
 }
 prime[0]=prime[1]=1;
 for(a=2;a<=1000000;a++)
  if(!prime[a])
   for(b=a;b<=1000000/a;b++)
    prime[a*b]=1;
 for(a=1;a<=1000000;a++)
  prefix[a+1]=prefix[a]+((!prime[a])&(!dev[a]));
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d",&a,&b);
  a++;
  b++;
  printf("%d\n",prefix[b]-prefix[a-1]);
 }
 return 0;
}
