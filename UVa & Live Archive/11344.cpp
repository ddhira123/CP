#include <cstdio>
#include <cstring>
using namespace std;

char c[1005];
bool bisa;
int len,tc;
int x,a;

bool bmod(int mod){
 int ret=0;
 for(int i=0;i<len;i++)
  ret=(ret*10+c[i]-'0')%mod;
 return ret==0; 
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%s",c);
  len=strlen(c);
  bisa=1;
  scanf("%d",&x);
  while(x--)
   scanf("%d",&a),bisa&=bmod(a);
  printf("%s - ",c);
  if(bisa)
   puts("Wonderful.");
  else
   puts("Simple.");  
 }
 return 0;
}
