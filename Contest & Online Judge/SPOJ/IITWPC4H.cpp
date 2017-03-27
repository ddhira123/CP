#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int cnt,arr[2][30],a,tc,s,b;
char x[1000030];

int main(){
 scanf("%d",&tc);
 while(tc--){
  for(a=0;a<2;a++){
   for(b=0;b<26;b++)
    arr[a][b]=0;
   scanf("%s",x);
   s=strlen(x);
   cnt=1;
   for(b=1;b<s;b++)
    if(x[b]!=x[b-1]){
     arr[a][x[b-1]-'a']=max(arr[a][x[b-1]-'a'],cnt);
     cnt=1;
    }
    else
     cnt++;
   arr[a][x[s-1]-'a']=max(arr[a][x[s-1]-'a'],cnt);
  }
  int ans=0;
  for(a=0;a<26;a++)
   ans=max(ans,arr[0][a]+arr[1][a]);
  printf("%d\n",ans);
 }
 return 0;
}
