#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

string s[105],dp2[105][105][10];
char x[15];
int tc,k,n,nil[105];
bool dp[105][105][10],visited[105][105][10],visited2[105][105][10];

bool PlayDP(int pos,int left,int mod){
 if(pos==n){
  if(left==0) return mod==0;
  return 0;
 }
 if(visited[pos][left][mod])
  return dp[pos][left][mod];
 visited[pos][left][mod]=1;
 bool ret=PlayDP(pos+1,left,mod);
 if(left>0) ret|=PlayDP(pos+1,left-1,(mod+nil[pos])%9);
 return dp[pos][left][mod]=ret;
}

string maks(string i,string j){
 if(i.length()>j.length()) return i;
 if(j.length()>i.length()) return j;
 for(int a=0;a<i.length();a++)
  if(i[a]>j[a]) return i;
  else if(j[a]>i[a]) return j;
 return i;
}

string cetak(int pos,int left,int mod){
 if(left==0) return "";
 else if(visited2[pos][left][mod]) return dp2[pos][left][mod];
 else{
  string ret="";
  //cout<<pos<<" "<<left<<" "<<mod<<"\n";
  if(PlayDP(pos+1,left-1,(mod+nil[pos])%9)){
   ret=maks(ret,s[pos]+cetak(pos+1,left-1,(mod+nil[pos])%9));
  }
  if(n-pos>left && PlayDP(pos+1,left,mod))
   ret=maks(ret,cetak(pos+1,left,mod));
  dp2[pos][left][mod]=ret;
  visited2[pos][left][mod]=1;
  return ret;
 }
}

bool cmp(string i,string j){
 return i+j>j+i;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d",&n,&k);
  for(int i=0;i<n;i++){
   scanf("%s",x);
   s[i]=(string)x;
   for(int j=0;j<=k;j++)
    for(int a=0;a<9;a++)
     visited[i][j][a]=visited2[i][j][a]=0;
  }
  sort(s,s+n,cmp);
  for(int i=0;i<n;i++){
   nil[i]=0;
   for(int j=0;j<s[i].length();j++)
    nil[i]+=s[i][j]-'0';
   nil[i]%=9;
  }
  bool ret=PlayDP(0,k,0);
  if(ret) cout<<cetak(0,k,0)<<"\n";
  else puts("-1");
 }
 return 0;
}

