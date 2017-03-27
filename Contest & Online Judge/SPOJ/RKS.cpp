#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

map<int,int> freq,fi;
int arr[1005],n,c,a;

bool cmp(int i,int j){
 if(freq[i]==freq[j])
  return fi[i]<fi[j];
 return freq[i]>freq[j];
}

int main(){
 scanf("%d%d",&n,&c);
 for(a=0;a<n;a++){
  scanf("%d",&arr[a]);
  if(fi.find(arr[a])==fi.end())
   fi[arr[a]]=a;
  freq[arr[a]]++;
 }
 sort(arr,arr+n,cmp);
 printf("%d",arr[0]);
 for(a=1;a<n;a++)
  printf(" %d",arr[a]);
 printf("\n");
 return 0;
}