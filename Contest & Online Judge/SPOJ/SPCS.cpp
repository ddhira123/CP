#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

char x[100005];
vector<char> v;
int tc;

bool pali(){
 int left=0,right=v.size()-1;
 while(left<right){
  if(v[left]!=v[right])
   return 0;
  left++;
  right--;
 }
 return 1;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%s",x);
  v.clear();
  v.push_back(x[0]);
  int s=strlen(x);
  for(int a=1;a<s;a++)
   if(x[a]!=x[a-1])
    v.push_back(x[a]);
  if(pali())
   printf("YES\n");
  else
   printf("NO\n");
 }
 return 0;
}
