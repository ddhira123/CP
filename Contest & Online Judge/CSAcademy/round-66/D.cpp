#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;

int match[N];
bool vis[N];
vector<int> adj[N];
int n;
int arr[N][N];

bool udah[N];
int inve[N];

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        for(int j = 1 ; j <= n ; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
}

int augment(int x) {
    if(vis[x]) return 0;
    vis[x] = 1;

    for(int nex : adj[x]) {
        if(match[nex] == -1 || augment(match[nex])) {
            match[nex] = x;
            return 1;
        }
    }

    return 0;
}

int mcbm() {
    memset(match, -1, sizeof match);
    int ret = 0;

    for(int i = 1 ; i <= n ; i++) {
        memset(vis, 0, sizeof vis);
        ret += augment(i);
    }

    return ret;
}

void solve() {
    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= n ; j++)
            if(arr[i][j]) {
                adj[i].push_back(j);
            }

    int ret = mcbm();

    // cout << ret << endl;

    if(ret == n) {
        for(int i = 1 ; i <= n ; i++) {
            inve[match[i]] = i;
            // printf("row %d col %d\n", match[i], i);
        }

        for(int i = 1 ; i <= n ; i++) {
            if(udah[i]) continue;
            int j = i;

            while(inve[j] != i) {
                udah[j] = 1;
                printf("R %d %d\n", i, inve[j]);
                j = inve[j];
            }

            udah[j] = 1;
        }
    } else {
        puts("-1");
    }

//     for(int i = 1 ; i <= n ; i++) {
//         adj[i].clear();
//     }

//     for(int i = 1 ; i <= n ; i++) {
//         for(int j = 1 ; j <= n ; j++) {
//             if(arr[i][j])
//         }
//     }
// }
}

int main() {
    read();
    solve();
    return 0;
}