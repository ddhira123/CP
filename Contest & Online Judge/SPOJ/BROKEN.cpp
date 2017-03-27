#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char x[1000005];
int l,r,freq[260],cnt,m,ans,s;

int main(){
 scanf("%d",&m);
 while(m){
  getchar();
  gets(x);
  l=cnt=ans=0;
  memset(freq,0,sizeof freq);
  s=strlen(x);
  for(r=0;r<s;r++){
   if(freq[x[r]]==0)
    cnt++;
   freq[x[r]]++;
   while(cnt>m){
    freq[x[l]]--;
    if(freq[x[l]]==0)
     cnt--;
    l++;
   }
   ans=max(ans,r-l+1);
  }
  printf("%d\n",ans);
  scanf("%d",&m);
 }
 return 0;
}
