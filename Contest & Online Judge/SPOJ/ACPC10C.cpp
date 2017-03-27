#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char x[32005];
int maxd,s,pos,tc;

bool solve(int depth){
 bool ans;
 if(x[pos]=='F')
  ans=0;
 else if(x[pos]=='T')
  ans=1;
 else{
  bool op=(maxd-depth)&1;
  ans=1-op;
  pos++;
  for(;x[pos]!=')';)
   if(op)
    ans|=solve(depth+1);
   else
    ans&=solve(depth+1);
 }
 pos++;
 return ans;
}

int main(){
 gets(x);
 while(strcmp(x,"()")){
  maxd=pos=0;
  s=strlen(x);
  int cnt=0;
  for(int a=0;a<s;a++){
   if(x[a]=='(')
    cnt++;
   if(x[a]==')')
    cnt--;
   maxd=max(cnt,maxd);
  }
  bool res=solve(1);
  printf("%d. ",++tc);
  if(!res)
   printf("false\n");
  else
   printf("true\n");
  //printf("%d %d\n",pos,s);
  gets(x);
 }
 return 0;
}