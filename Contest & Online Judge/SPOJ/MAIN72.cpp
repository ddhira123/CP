#include <cstdio>
using namespace std;
#define max_n 100001

bool visited[101][max_n],valid[max_n];
int tc,n,arr[101];

void rec(int pos,int sum){
 if(pos==n){
  valid[sum]=1;
  return;
 }
 if(visited[pos][sum])
  return;
 visited[pos][sum]=1;
 rec(pos+1,sum);
 rec(pos+1,sum+arr[pos]);
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  int jum=0;
  for(int a=0;a<n;a++){
   scanf("%d",&arr[a]);
   jum+=arr[a];
  }
  for(int a=0;a<=jum;a++){
   valid[a]=0;
   for(int b=0;b<n;b++)
    visited[b][a]=0;
  }
  rec(0,0);
  long long ans=0;
  for(int a=1;a<=jum;a++)
   if(valid[a]){
    ans+=a;
    //printf("%d\n",a);
   }
  printf("%lld\n",ans);
 }
 return 0;
}