#include <cstdio>
#include <cstring>
using namespace std;
#define MAX_N 100010

int arr[MAX_N],tc,n,b[MAX_N],m;
char p[MAX_N],t[MAX_N];

void pre(){
 int i=0,j=-1;b[0]=-1;
 while(i<m){
  while(j>=0 && p[i]!=p[j]) j=b[j];
  i++; j++;
  b[i]=j;
 }
}

bool kmp(){
 int i=0,j=0;
 while(i<n-1){
  while(j>=0 && t[i]!=p[j]) j=b[j];
  i++;
  j++;
  if(j==m)
   return 1;
 }
 return 0;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  scanf("%d",&arr[0]);
  for(int a=1;a<n;a++){
   scanf("%d",&arr[a]);
   if(arr[a]>arr[a-1])
    t[a-1]='G';
   else if(arr[a]<arr[a-1])
    t[a-1]='L';
   else
    t[a-1]='E';
  }
  scanf("%s",p);
  m=strlen(p);
  pre();
  bool ans=kmp();
  if(ans)
   printf("YES\n");
  else
   printf("NO\n");
 }
 return 0;
}