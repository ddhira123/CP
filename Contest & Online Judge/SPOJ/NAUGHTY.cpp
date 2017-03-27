#include <cstdio>
#include <algorithm>
using namespace std;

int freq[100005][5],a,b,n,tgt,left,ans;

int main(){
 scanf("%d",&n);
 tgt=(n+1)/2;
 for(int i=0;i<n;i++){
  scanf("%d %d",&a,&b);
  if(a==b)
   freq[a][2]++;
  else{
   freq[a][0]++;
   freq[b][1]++;
  }
 }
 ans=1000000000;
 for(int i=0;i<=100000;i++)
  if(freq[i][0]+freq[i][1]+freq[i][2]>=tgt){
   left=tgt-(freq[i][0]+freq[i][2]);
   if(left<=0)
    left=0;
   ans=min(ans,left);
  }
 if(ans==1000000000)
  printf("Impossible\n");
 else
  printf("%d\n",ans);
 return 0;
}