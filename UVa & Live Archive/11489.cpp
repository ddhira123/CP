#include <cstdio>
#include <cstring>
using namespace std;

int cnt[5];
int sum;
char c[1005];
int tc;

int main(){
 scanf("%d",&tc);
 for(int t=1;t<=tc;t++){
  bool win;
  sum=cnt[0]=cnt[1]=cnt[2]=0;
  scanf("%s",c);
  int len=strlen(c);
  for(int i=0;i<len;i++)
   sum+=c[i]-'0',cnt[(c[i]-'0')%3]++;
  sum%=3; 
  if(sum){
   if(cnt[sum]){
    if(cnt[0]&1) win=0;
    else         win=1;
   }
   else
    win=0;
  }
 else
  win=(cnt[0]&1);
  printf("Case %d: %c\n",t,(win ? 'S' : 'T'));  
 }
}
