#include <iostream>
#include <vector>
using namespace std;

long long dp[105][105][2];
string x,tmp;
vector<int> op,nil;
int siz,a,b,len,tc;

long long solve(int l,int r,int val){
 if(l==r)
  return nil[l]==val;
 if(dp[l][r][val]!=-1)
  return dp[l][r][val];
 long long res=0;
 for(int i=l;i<r;i++)
  if(val){
   if(op[i]==0)
    res+=solve(l,i,1)*solve(i+1,r,1);
   if(op[i]==1)
    res+=solve(l,i,1)*solve(i+1,r,1)+solve(l,i,0)*solve(i+1,r,1)+solve(l,i,1)*solve(i+1,r,0);
   if(op[i]==2)
    res+=solve(l,i,1)*solve(i+1,r,0)+solve(l,i,0)*solve(i+1,r,1);
  }
  else{
   if(op[i]==0)
    res+=solve(l,i,0)*solve(i+1,r,0)+solve(l,i,0)*solve(i+1,r,1)+solve(l,i,1)*solve(i+1,r,0);
   if(op[i]==1)
    res+=solve(l,i,0)*solve(i+1,r,0);
   if(op[i]==2)
    res+=solve(l,i,1)*solve(i+1,r,1)+solve(l,i,0)*solve(i+1,r,0);
  }
  return dp[l][r][val]=res;
}

int main(){
 cin>>tc;
 getline(cin,x);
 while(tc--){
  op.clear();
  nil.clear();
  tmp="";
  getline(cin,x);
  len=x.length();
  for(a=0;a<len;a++)
   if(x[a]==' '){
    if(tmp=="T")
     nil.push_back(1);
    else if(tmp=="F")
     nil.push_back(0);
    else if(tmp=="and")
     op.push_back(0);
    else if(tmp=="or")
     op.push_back(1);
    else if(tmp=="xor")
     op.push_back(2);
    tmp="";
   }
   else
    tmp+=x[a];
  if(tmp=="T")
   nil.push_back(1);
  else if(tmp=="F")
   nil.push_back(0);
  siz=nil.size();
  for(a=0;a<siz;a++)
   for(b=0;b<siz;b++)
    dp[a][b][0]=dp[a][b][1]=-1;
  cout<<solve(0,siz-1,1)<<"\n";
 }
 return 0;
}
