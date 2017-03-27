#include <cstdio>
using namespace std;

int prefix[15][1000005],fak[1000005],a,b,n,tc;
bool flag[1000005];

int main(){
 for(a=2;a<=1000000;a++)
  if(!flag[a]){
   fak[a]=1;
   for(b=2;b<=1000000/a;b++){
    flag[a*b]=1;
    fak[a*b]++;
   }
  }
 for(a=1;a<=1000000;a++){
  for(b=0;b<=10;b++)
   prefix[b][a]=prefix[b][a-1];
  prefix[fak[a]][a]++;
 }
 scanf("%d",&tc);
 while(tc--){
  scanf("%d%d%d",&a,&b,&n);
  printf("%d\n",prefix[n][b]-prefix[n][a-1]);
 }
 return 0;
}