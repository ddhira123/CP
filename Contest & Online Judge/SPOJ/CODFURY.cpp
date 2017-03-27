#include <cstdio>
#include <algorithm>
using namespace std;

pair<int,int> ans;
int tc,p,m,arr[50005],l,sum,r;

int main(){
 scanf("%d",&tc);
 while(tc--){
  ans=make_pair(0,0);
  l=sum=0;
  scanf("%d %d",&p,&m);
  for(r=0;r<p;r++){
   scanf("%d",&arr[r]);
   sum+=arr[r];
   while(sum>m)
    sum-=arr[l++];
   if(r-l+1>ans.second){
    ans.first=sum;
    ans.second=r-l+1;
   }
   else if(r-l+1==ans.second)
    ans.first=min(ans.first,sum);
  }
  printf("%d %d\n",ans.first,ans.second);
 }
 return 0;
}