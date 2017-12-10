#include <bits/stdc++.h>
using namespace std;
 
const int N = 2030;
const int INF = 1e9;
 
int a[N + 5][N + 5],u[N + 5],v[N + 5];
bool used[N + 5];
int p[N + 5],way[N + 5];
int minv[N + 5];
int ans[N + 5];
int arr[N + 5];
int n, k;
int m;
 
void read() {
    scanf("%d %d %d",&n, &m, &k);

    n = max(n, m);
    m = max(n, m);

    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= m ; j++) {
            a[i][j] = 0;
        }

    for(int i = 1 ; i <= k ; i++) {
        int p, q, r;
        scanf("%d %d %d", &p, &q, &r);

        a[p][q] = -r;
    }
}
 
void prepare() {
    for(int i = 0 ; i <= m ; i++) {
        u[i] = v[i] = p[i] = way[i] = 0;
    }
}
 
void hungarian(){
    prepare();
 
    for(int i = 1 ; i <= m ; i++){
        p[0] = i;
        int j0 = 0;
        for(int j = 0 ; j <= m ; j++)
            minv[j] = INF,used[j] = 0;
        do{
            used[j0] = 1;
            int i0 = p[j0],delta = INF, j1;
            for(int j = 1 ; j <= m ; j++)
                if(!used[j]){
                    int cur = a[i0][j] - u[i0] - v[j];
                    if(cur < minv[j])
                        minv[j] = cur,way[j] = j0;
                    if(minv[j] < delta)
                        delta = minv[j], j1 = j;     
                }
            for(int j = 0 ; j <= m ; j++)
                if(used[j])
                   u[p[j]] += delta,  v[j] -= delta; 
                else
                   minv[j] -= delta;  
            j0 = j1;           
        }while(p[j0] != 0); 
        
        do{
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        }while(j0);   
    }

    int sum = 0;
    vector<pair<int, int>> ret;
 
    for(int i = 1 ; i <= m ; i++)
        ans[p[i]] = i;
 
    // for(int i = 1 ; i <= m ; i++)
    //     printf("%d-th row matched with %d-th column\n",i,ans[i])
    for(int i = 1 ; i <= m ; i++) {
        if(a[i][ans[i]]) {
            ret.push_back({i, ans[i]});
            sum += a[i][ans[i]];
        }
    }

    cout << -sum << endl;
    cout << ret.size() << endl;
    for(auto x : ret) {
        cout << x.first << " " << x.second << endl;
    }
}
 
int main() {
    read();
    hungarian();
    return 0;
} 