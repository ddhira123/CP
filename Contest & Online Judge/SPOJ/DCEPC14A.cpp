#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXX = 100000;
const int N = 305;

vector<pair<int,int> > v[MAXX + 5];
int BIT[N][N];
int r,c;
unsigned ans;

void Update(int rr,int cc){
    for(int i = rr ; i <= r ; i += i & -i)
        for(int j = cc ; j <= c ; j += j & -j)
            BIT[i][j]++;
}

unsigned Query(int rr,int cc){
    unsigned res = 0;
    for(int i = rr ; i ; i -= i & -i)
        for(int j = cc ; j ; j -= j & -j)
            res += BIT[i][j];
    return res;        
}

int main(){
    scanf("%d %d",&r,&c);
    for(int i = 1 ; i <= r ; i++)
        for(int j = 1 ; j <= c ; j++){
            int x;
            scanf("%d",&x);
            v[x].push_back(make_pair(i,j));
        }
    for(int i = MAXX ; i >= 0 ; i--){
        for(int j = 0 ; j < v[i].size() ; j++)
            ans += Query(v[i][j].first,v[i][j].second);
        for(int j = 0 ; j < v[i].size() ; j++)
            Update(v[i][j].first,v[i][j].second);    
    }    
    printf("%u\n",ans);
    return 0;
}