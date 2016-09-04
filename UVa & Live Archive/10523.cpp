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

inline string clean(string x){
 int len=x.length()-1;
 for(int i=len;i>=0;i--)
  if(x[i]=='0')
   x.erase(x.begin()+i);
  else break;
 if(x=="") x="0";
 return x;
}

inline bool biggreat(string a,string b){
 int lena=a.length();
 int lenb=b.length();
 int sz=max(lena,lenb);
 for(int i=0;i<sz-lena;i++)
  a=a+"0";
 for(int i=0;i<sz-lenb;i++)
  b=b+"0";
 for(int i=sz-1;i>=0;i--)
  if(a[i]>b[i]) return 1;
  else if(a[i]<b[i]) return 0;
 return 0;  
}

inline bool bigless(string a,string b){
 int lena=a.length();
 int lenb=b.length();
 int sz=max(lena,lenb);
 for(int i=0;i<sz-lena;i++)
  a=a+"0";
 for(int i=0;i<sz-lenb;i++)
  b=b+"0";
 for(int i=sz-1;i>=0;i--)
  if(a[i]<b[i]) return 1;
  else if(a[i]>b[i]) return 0;
 return 0;  
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
 ans=clean(ans);  
 return ans;   
}

string bigmul(string a,string b){
 //if(a=="0" || b=="0") return "0";
 string ans="",trail="";
 if(a.length()<b.length()) swap(a,b);
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
 ans=clean(ans);
 return ans;
}

int n,a;

string dp[155][20];

int main(){
 ios_base::sync_with_stdio(false);
 for(int i=0;i<=15;i++){
  string base=itostr(i);
  string po="1";
  dp[0][i]="0";
  for(int j=1;j<=150;j++){
   string mul=itostr(j);
   po=bigmul(po,base);
   dp[j][i]=bigsum(dp[j-1][i],bigmul(mul,po));
  }
 }
 while(cin>>n){
  cin>>a;
  cout<<rev(dp[n][a])<<"\n";
 }
 return 0;
}
