#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

//satuan dari index 0

inline string rev(string x){
 reverse(x.begin(),x.end());
 return x;
}

inline string itostr(int x){
 if(x==0) return "0";
 char res[5]="";
 int it=0;
 while(x){
  res[it++]=x%10+'0';
  x/=10;
 }
 return (string)(res);
}

string bigsum(string a,string b){
 int lena=a.length(),lenb=b.length();
 int sz=max(lena,lenb);
 for(int i=0;i<sz-lena;i++)
  a=a+"0";
 for(int i=0;i<sz-lenb;i++)
  b=b+"0";
 int carry=0;
 string ans=""; 
 for(int i=0;i<sz;i++){
  int tmp=carry+a[i]-'0'+b[i]-'0';
  ans=ans+itostr(tmp%10);
  carry=tmp/10;
 }
 if(carry)
   ans=ans+itostr(carry);
 return ans;   
}

string bigmul(string a,string b){
 if(a=="0" || b=="0") return "0";
 string ans="",trail="";
 if(b.length()==1){
  int lena=a.length();
  int carry=0;
  for(int i=0;i<lena;i++){
   int tmp=carry+(a[i]-'0')*(b[0]-'0');
   ans=ans+itostr(tmp%10);
   carry=tmp/10;
  }
  if(carry)
   ans=ans+itostr(carry);
 }
 else{
  int lena=a.length(),lenb=b.length();
  ans="0";
  for(int i=0;i<lenb;i++){
   ans=bigsum(ans,trail+bigmul(a,itostr(b[i]-'0')) );
   trail=trail+"0";
  }
 }
 return ans;
}

int main(){
 ios_base::sync_with_stdio(false);
 string x,y;
 while(cin>>x){
  cin>>y;
  cout<<rev(bigmul(rev(x),rev(y)))<<"\n";
 }
 return 0;
}
