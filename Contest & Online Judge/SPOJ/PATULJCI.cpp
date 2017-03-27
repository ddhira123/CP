#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100005;
const int TIMES = 17;

vector<int> v[N];
int arr[3 * N];
int n,c,q;

int query(int color,int lo,int hi){
    return upper_bound(v[color].begin(),v[color].end(),hi) - lower_bound(v[color].begin(),v[color].end(),lo);
}

int range_random(int lo,int hi){
    unsigned range = hi - lo + 1;
    unsigned add = rand() % range;
    return lo + add;
}

int main(){
    scanf("%d %d",&n,&c);
    for(int i = 1 ; i <= n ; i++){
        scanf("%d",&arr[i]);
        v[arr[i]].push_back(i);
    }
    scanf("%d",&q);
    while(q--){
        int ans = -1;
        int lo,hi,k;
        scanf("%d %d",&lo,&hi);
        k = (hi - lo + 1) / 2;
        for(int i = 0 ; i < TIMES && ans == -1 ; i++){
            int color = range_random(lo,hi);
            color = arr[color];
            if(query(color,lo,hi) > k)
                ans = color;
        }
        if(ans == -1)
            puts("no");
        else
            printf("yes %d\n",ans);    
    }
    return 0;
}