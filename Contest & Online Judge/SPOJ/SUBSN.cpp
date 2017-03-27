#include <cstdio>
#include <cstring>
using namespace std;

char x[100005],y[205];
int tc,q,s,t,i,next[100005][30],n;

int main(){
 scanf("%d",&tc); getchar();
 for(i=1;i<=tc;i++){
  gets(x);
  s=strlen(x);
  for(int a=0;a<26;a++)
   next[s][a]=s;
  for(int a=s-1;a>=0;a--){
   for(int b=0;b<26;b++)
    next[a][b]=next[a+1][b];
   next[a][x[a]-'a']=a;
  }
  printf("Case %d:\n",i);
  scanf("%d",&q); getchar();
  while(q--){
   gets(y);
   n=strlen(y);
   bool bisa=0;
   int now=-1,j=0;
    while(now<s){
     if(j==n){
      bisa=1;
      break;
     }
     now=next[now+1][y[j]-'a'];
     j++;
    }
   if(bisa)
    printf("YES\n");
   else
    printf("NO\n");
  }
 }
 return 0;
}