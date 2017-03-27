#include <cstdio>
#include <cstring>
using namespace std;

char x[100005],y[100005];
int jum1[30],jum2[30],tc,n,m,a;
bool ans,tmp;

int main(){
 scanf("%d",&tc);
 while(tc--){
  for(a=0;a<26;a++)
   jum1[a]=jum2[a]=0;
  scanf("%s",x);
  scanf("%s",y);
  n=strlen(x);
  m=strlen(y);
  for(a=0;a<m;a++){
   jum2[y[a]-'a']++;
   jum1[x[a]-'a']++;
  }
  ans=0;
  tmp=1;
  for(a=0;a<26&&tmp;a++)
   tmp&=(jum1[a]==jum2[a]);
  ans|=tmp;
  for(a=m;a<n&&!ans;a++){
   jum1[x[a-m]-'a']--;
   jum1[x[a]-'a']++;
   tmp=1;
   for(int b=0;b<26&&tmp;b++)
    tmp&=(jum1[b]==jum2[b]);
   ans|=tmp;
  }
  if(ans)
   printf("YES\n");
  else
   printf("NO\n");
 }
 return 0;
}
