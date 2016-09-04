#include <cstdio>
using namespace std;

const int N = 1005;

int move[3] = {2,3,5};
int grundy[7] = {0,0,1,1,2,2,3};

int Nim(int x){
    return grundy[x % 7];
}

int arr[N];
int n,tc;

void Update(int &take,int &num,int a,int b){
    if(take < a)
        take = a,num = b;
}

int main(){
    scanf("%d",&tc);
    for(int t = 1 ; t <= tc ; t++){
        int sum = 0;
        int take = 0;
        int num;
        scanf("%d",&n);
        for(int i = 1 ; i <= n ; i++){
            scanf("%d",&arr[i]);
            sum ^= Nim(arr[i]);
        }
        for(int i = 1 ; i <= n ; i++)
            for(int j = 0 ; j < 3 ; j++)
                if(arr[i] >= move[j]){
                    sum ^= Nim(arr[i]);
                    sum ^= Nim(arr[i] - move[j]);
                    if(sum == 0)
                        Update(take,num,move[j],i);
                    sum ^= Nim(arr[i] - move[j]);
                    sum ^= Nim(arr[i]);
                }
        if(take == 0)
            puts("Robert wins.");
        else{
            puts("Julia wins.");
            printf("Take %d sticks from heap number %d.\n",take,num);
        }
        puts("");
    }
    return 0;
}
