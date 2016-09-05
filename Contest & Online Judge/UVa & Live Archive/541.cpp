#include <cstdio>
using namespace std;

int jum[2];
int row[105],col[105];
int x,n;

inline void proc(){
 if(jum[1]==0){
  puts("OK");
  return;
 }
 for(int i=0;i<n;i++)
  for(int j=0;j<n;j++){
   int tmp[2];
   tmp[0]=jum[0];
   tmp[1]=jum[1];
   tmp[row[i]]--;
   tmp[col[j]]--;
   tmp[(1+row[i])&1]++;
   tmp[(1+col[j])&1]++;
   if(tmp[1]==0){
    printf("Change bit (%d,%d)\n",i+1,j+1);
    return;
   }
  }
 puts("Corrupt"); 
}

int main(){
 scanf("%d",&n);
 while(n){
  jum[0]=jum[1]=0;
  for(int i=0;i<n;i++)
   row[i]=col[i]=0;
  for(int i=0;i<n;i++)
   for(int j=0;j<n;j++)
    scanf("%d",&x),row[i]+=x,col[j]+=x;
  for(int i=0;i<n;i++){
   row[i]&=1;
   col[i]&=1;
   jum[row[i]]++;
   jum[col[i]]++;
  }   
  proc();
  scanf("%d",&n);
 }
 return 0;
}
