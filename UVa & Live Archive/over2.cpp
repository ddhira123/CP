#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string arr[15];
int tc,n;

string proc(string a,string b){
 int len1,len2,i,j;
 len1=a.length();
 len2=b.length();
 for(i=len1-len2;i<=len1;i++){
  for(j=0;j<len2 && j+i<len1;j++)
   if(a[i+j]!=b[j]) break;
  if(i+j==len1){
   string ret="";
   for(int k=j;k<len2;k++)
    ret=ret+b[k];
   return ret; 
  } 
 }
}

int rec(string now,int mask){
 if(mask==0) return now.length();
 int ans=1000000000;
 for(int i=0;i<n;i++)
  if(mask&(1<<i))
   ans=min(ans,rec(now+proc(now,arr[i]),mask^(1<<i)));
 return ans;  
}

int main(){
 cin>>tc;
 for(int t=1;t<=tc;t++){
  cin>>n;
  for(int i=0;i<n;i++)
   cin>>arr[i];
  cout<<"Case "<<t<<": "<<rec("",(1<<n)-1)<<"\n"; 
 }
 return 0;
}
