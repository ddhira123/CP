#include <cstdio>
#include <vector>
using namespace std;

vector<int> v[2];
int l[2],r[2],n,k,tc;
char x[1005];

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d",&n,&k);
  scanf("%s",x);
  v[0].clear(); v[1].clear();
  l[0]=l[1]=0;
  for(int i=0;i<n;i++)
   v[x[i]-'0'].push_back(i);
  r[0]=v[0].size()-1;
  r[1]=v[1].size()-1;
  for(int i=0;i<n-k;i++)
   if(i&1){
    if(l[0]<=r[0])
     l[0]++;
    else
     r[1]--;
   }
   else{
    if(l[1]<=r[1])
     l[1]++;
    else
     r[0]--;
   }
  while(l[0]<=r[0] && l[1]<=r[1]){
   if(v[0][l[0]]<v[1][l[1]])
    printf("0"),l[0]++;
   else
    printf("1"),l[1]++;
  }
  while(l[0]<=r[0])
   printf("0"),l[0]++;
  while(l[1]<=r[1])
   printf("1"),l[1]++;
  printf("\n");
 }
 return 0;
}
