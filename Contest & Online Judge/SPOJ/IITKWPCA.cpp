#include <set>
#include <iostream>
using namespace std;

set<string> s;
string x,tmp;
int tc;

int main(){
 cin>>tc;
 getline(cin,x);
 while(tc--){
  s.clear();
  tmp="";
  getline(cin,x);
  int siz=x.length();
  for(int a=0;a<siz;a++)
   if(x[a]!=' ')
    tmp+=x[a];
   else if(tmp!=""){
    s.insert(tmp);
    tmp="";
   }
   if(tmp!="")
    s.insert(tmp);
   cout<<s.size()<<"\n";
 }
 return 0;
}
