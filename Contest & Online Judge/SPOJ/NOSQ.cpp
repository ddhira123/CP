#include <cstdio>
using namespace std;

int rsq[100005][15];
bool flag[100005];

int main(){
 for(int a=2;a<=316;a++)
  for(int b=1;b<=100000/(a*a);b++)
   flag[a*a*b]=1;
 for(int a=1;a<=100000;a++){
  for(int b=0;b<10;b++)
   rsq[a][b]=rsq[a-1][b];
  if(!flag[a]){
   bool tmp[15];
   for(int b=0;b<10;b++)
    tmp[b]=0;
   int c=a;
   while(c){
    tmp[c%10]=1;
    c/=10;
   }
   for(int b=0;b<10;b++)
    rsq[a][b]+=tmp[b];
  }
 }
 int tc,a,b,k;
 scanf("%d",&tc);
 while(tc--){
  scanf("%d%d%d",&a,&b,&k);
  printf("%d\n",rsq[b][k]-rsq[a-1][k]);
 }
 return 0;
}