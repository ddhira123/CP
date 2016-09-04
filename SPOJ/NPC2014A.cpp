#include <cstdio>
using namespace std;

int grundy(int x){
    if(x <= 1) return 0;
    int res = 0;
    while((x & 1) == 0){
        res++;
        x >>= 1;
    }
    return res;
}

int main(){
    int tc;
    scanf("%d",&tc);
    while(tc--){
        int n;
        scanf("%d",&n);
        int nim = 0;
        while(n--){
            int x;
            scanf("%d",&x);
            nim ^= grundy(x);
        }
        if(nim)
            puts("Puguh is the bestest player in teh wurld");
        else
            puts("Joke is the bestest player in teh wurld");
    }
    return 0;
}
