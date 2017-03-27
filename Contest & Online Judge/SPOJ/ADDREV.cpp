#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> y1,y2,ans;
string x1,x2;
int a,tc;

vector<int> bigsum(vector<int> v1,vector<int> v2){
 vector<int> p1=v1,p2=v2,jwb;
 jwb.clear();
 int k,carry=0;
 while(p1.size()<p2.size())
  p1.push_back(0);
 while(p2.size()<p1.size())
  p2.push_back(0);
 for(k=0;k<p1.size();k++){
  jwb.push_back((p1[k]+p2[k]+carry)%10);
  carry=(p1[k]+p2[k]+carry)/10;
 }
 if(carry>0)
  jwb.push_back(carry);
 return jwb;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  y1.clear();
  y2.clear();
  cin>>x1>>x2;
  for(a=0;a<x1.length();a++)
   y1.push_back(x1[a]-'0');
  for(a=0;a<x2.length();a++)
   y2.push_back(x2[a]-'0');
 // while(y1[y1.size()-1]==0)
  // y1.pop_back();
  //while(y2[y2.size()-1]==0)
   //y2.pop_back();
  ans=bigsum(y1,y2);
  reverse(ans.begin(),ans.end());
  while(ans[ans.size()-1]==0)
   ans.pop_back();
  for(a=ans.size()-1;a>=0;a--)
   printf("%d",ans[a]);
  printf("\n");
 }
 return 0;
}
