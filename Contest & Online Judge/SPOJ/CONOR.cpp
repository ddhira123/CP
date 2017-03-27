#include <cstdio>
using namespace std;

const int MAXX = 605;

int arr[MAXX][MAXX];
int BIT[MAXX][MAXX];
int r,c,q;

void Update(int row,int col,int val){
 for(int i = row ; i <= r ; i += i & -i)
    for(int j = col ; j <= c ; j += j & -j)
        BIT[i][j] ^= val;
}

int Query(int row,int col){
 int res = 0;
 for(int i = row ; i > 0 ; i -= i & -i)
    for(int j = col ; j > 0 ; j -= j & -j)
        res ^= BIT[i][j];
 return res;
}

int main(){
 scanf("%d %d",&r,&c);

 for(int i = 1 ; i <= r ; i++)
    for(int j = 1 ; j <= c ; j++){
        scanf("%d",&arr[i][j]);
        Update(i, j, arr[i][j]);
    }

 scanf("%d",&q);
 while(q--){
  int r1,c1;
  int r2,c2;
  int op,val;
  scanf("%d",&op);

  if(op == 1){
    scanf("%d %d %d",&r1,&c1,&val);
    r1++; c1++;
    Update(r1, c1, arr[r1][c1]);
    Update(r1, c1, val);
    arr[r1][c1] = val;
  }
  else{
    scanf("%d %d %d %d",&r1,&c1,&r2,&c2);
    r1++; c1++; r2++; c2++;
    int ans = Query(r2,c2);
    ans ^= Query(r2,c1 - 1);
    ans ^= Query(r1 - 1,c2);
    ans ^= Query(r1 - 1,c1 - 1);
    printf("%d\n",ans);
  }
 }
 return 0;
}
