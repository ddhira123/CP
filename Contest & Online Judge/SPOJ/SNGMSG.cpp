#include <cstdio>
#include <cstring>
using namespace std;

char x[505],key[25];
int tc,it,op,pos;

int main(){
 scanf("%d",&tc); getchar();
 while(tc--){
  pos=0;
  op=1;
  gets(key);
  gets(x);
  int len=strlen(x),len2=strlen(key);
  for(int i=0;i<len;i++){
   int z=x[i]-(key[pos]-'0');
   //while(z>'z') z-=26;
   while(z<'a') z+=26;
   printf("%c",z);
   pos+=op;
   if(pos==len2){
    pos=len2-1;
    op=-1;
   }
   else if(pos==-1){
    pos=0;
    op=1;
   }
  }
  puts("");
 }
 return 0;
}
