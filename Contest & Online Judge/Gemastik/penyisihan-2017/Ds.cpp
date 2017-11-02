#include <bits/stdc++.h>
using namespace std;

typedef pair<int, pair<int,int>> data;

const int N = 55;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};

int dist[N][N][N];
int height[N][N];
int dp[N][N];
int rowS[N], colS[N];
int minCost[N][N];
int comb[N][N];
int r, c, n;

int get_comb(int n, int k) {
    if(n < 0 || k < 0 || n < k) {
        return 0;
    }

    return comb[n][k];
}

void init() {
    for(int i = 0 ; i < N ; i++) {
        comb[i][0] = 1;
        for(int j = 1 ; j <= i ; j++) {
            comb[i][j] = (comb[i-1][j] + comb[i-1][j-1]) % MOD;
        }
    }
}

void read() {
    scanf("%d %d %d", &r, &c, &n);
    for(int i = 0 ; i < r ; i++)
        for(int j = 0 ; j < c ; j++) {
            scanf("%d", &height[i][j]);

            if(height[i][j] < 0) {
                int idx = -height[i][j] - 1;
                height[i][j] = 0;

                rowS[idx] = i;
                colS[idx] = j;
            }
        }
}

void dijkstra(int column) {
    for(int i = 0 ; i < r ; i++)
        for(int j = 0 ; j < c ; j++) {
            dist[column][i][j] = INF;
        }
    dist[column][0][column] = 1;

    priority_queue<data> pq;

    pq.push({-1, {0, column}});

    while(!pq.empty()) {
        auto cur = pq.top();
        pq.pop();

        int dis = -cur.first;
        int row = cur.second.first;
        int col = cur.second.second;

        if(dis != dist[column][row][col]) continue;

        // printf("%d %d %d -> %d\n", column, row, col, dis);

        for(int i = 0 ; i < 4 ; i++) {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if(nr >= 0 && nr < r && nc >= 0 && nc < c) {
                int ndis = dis + 1 + abs(height[row][col] - height[nr][nc]);

                if(ndis < dist[column][nr][nc]) {
                    dist[column][nr][nc] = ndis;
                    pq.push({-ndis, {nr, nc}});
                }
            }
        }
    }
}

void prepare() {
    for(int i = 0 ; i < c ; i++) {
        dijkstra(i);

        for(int j = 0 ; j < n ; j++)
            minCost[i][j] = dist[i][rowS[j]][colS[j]];
    }
}

int solve_n_1() {
    int ret = 0;
    for(int col = 0 ; col < c ; col++)
        ret = (ret + minCost[col][0]) % MOD;
    return ret;
}

int main() {
    init();

    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        prepare();

        if(n == 1) {
            cout << solve_n_1() << endl;
        }
    }
    return 0;
}