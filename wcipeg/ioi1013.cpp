#include <iostream>
using namespace std;

int arr[3005][3005];
int pref[3005][3005];
int r,c,w,h;

bool valid(int x){
 //cout<<x<<"\n";
 for(int i=1;i<=r;i++){
  for(int j=1;j<=c;j++){
   if(arr[i][j] > x) pref[i][j]=1;
   else if(arr[i][j] < x) pref[i][j]=-1;
   else                   pref[i][j]=0;
   pref[i][j]+=pref[i-1][j];
   pref[i][j]+=pref[i][j-1];
   pref[i][j]-=pref[i-1][j-1];
   //cout<<pref[i][j]<<" ";
  }
  //cout<<"\n";
 }
 for(int i=h;i<=r;i++)
  for(int j=w;j<=c;j++)
   if(pref[i][j] - pref[i-h][j] - pref[i][j-w] + pref[i-h][j-w] <= 0)
    return 1;
 return 0;
}

int main(){
 ios_base::sync_with_stdio(0);
 cin>>r>>c>>h>>w;
 for(int i=1;i<=r;i++)
  for(int j=1;j<=c;j++)
   cin>>arr[i][j];
 int lo=1,hi=r*c;
 //cout<<valid(9)<<"\n";
 while(lo<hi){
  //cout<<lo<<" "<<hi<<"\n";
  int mi=(lo+hi)>>1;
  if(valid(mi)) hi=mi;
  else lo=mi+1;
 }
 cout<<lo<<"\n";
 return 0;
}

