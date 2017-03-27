#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char x[100005],y[100005];
int len,b[100005];

void playPre(){
 int i=0,j=-1;b[0]=-1;
 while(i<len){
  while(j>=0 && y[i]!=y[j]) j=b[j];
  j++;i++;
  b[i]=j;
 }
}

void playKMP(){
 int i=0,j=0;
 while(i<len){
  while(j>=0 && x[i]!=y[j]) j=b[j];
  i++;
  j++;
 }
 printf("%s",x);
 for(i=j;i<len;i++)
    printf("%c",y[i]);
 printf("\n");
}

int main(){
 while(gets(x)){
  len=strlen(x);
  strcpy(y,x);
  reverse(y,y+len);
  playPre();
  playKMP();
 }
 return 0;
}
