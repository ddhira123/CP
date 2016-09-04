#include <iostream>
#include <cmath>
using namespace std;
#define eps 1e-9
char c;
double le[20],up[20],rig[20],down[20];
int it;
double x,y;

int main(){
 ios_base::sync_with_stdio(false);
 cin>>c;
 int it=0;
 while(c!='*'){
  cin>>le[it]>>up[it]>>rig[it]>>down[it];
  it++;
  cin>>c;
 }
 int n=0;
 cin>>x>>y;
 while(fabs(x-9999.9)>eps && fabs(y-9999.9)>eps){
  n++;
  bool found=0;
  for(int i=0;i<it;i++)
   if(le[i]<x && x<rig[i] && down[i]<y && y<up[i]){
    found=1;
    cout<<"Point "<<n<<" is contained in figure "<<i+1<<"\n";
   }
  if(!found)
   cout<<"Point "<<n<<" is not contained in any figure\n";
  cin>>x>>y;
 }
 return 0;
}
